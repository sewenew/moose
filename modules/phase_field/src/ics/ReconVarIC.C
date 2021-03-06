#include "ReconVarIC.h"

template<>
InputParameters validParams<ReconVarIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRequiredParam<UserObjectName>("ebsd_reader", "The EBSDReader GeneralUserObject");
  params.addRequiredParam<bool>("consider_phase", "If true, IC will only only deal with grain values and ignore phase");
  params.addParam<unsigned int>("phase", 0, "EBSD phase number to be assigned to this grain");
  params.addParam<bool>("all_to_one", false, "If true, assign all grain numbers in this phase to the same variable");
  params.addParam<unsigned int>("op_num", 0, "Specifies the number of order paraameters to create, all_to_one = false");
  params.addParam<unsigned int>("op_index", 0, "The index for the current order parameter, if all_to_one = false");
  return params;
}

ReconVarIC::ReconVarIC(const InputParameters & parameters) :
    InitialCondition(parameters),
    _mesh(_fe_problem.mesh()),
    _nl(_fe_problem.getNonlinearSystem()),
    _ebsd_reader(getUserObject<EBSDReader>("ebsd_reader")),
    _consider_phase(getParam<bool>("consider_phase")),
    _phase(getParam<unsigned int>("phase")),
    _all_to_one(getParam<bool>("all_to_one")),
    _op_num(getParam<unsigned int>("op_num")),
    _op_index(getParam<unsigned int>("op_index"))
{
  if (!_consider_phase && _all_to_one)
    mooseError("In ReconVarIC, if you are not considering phase, you can't assign all grains to one variable");

  if (_consider_phase)
    mooseError("In ReconvarIC, setting ics from phase informtation is not currently supported");
}

void
ReconVarIC::initialSetup()
{
  //Get the number of grains from the EBSD data, for the specified phase
  if (_consider_phase)
    _grain_num = _ebsd_reader.getGrainNum(_phase);
  else
    _grain_num = _ebsd_reader.getGrainNum();

  if (!_all_to_one)
  {
    // Output error message
    if (_op_num > _grain_num)
      mooseError("ERROR in PolycrystalReducedIC: Number of order parameters (op_num) can't be larger than the number of grains (grain_num)");

    //Because the grains start at 1 in phase 1
    unsigned int grn_index_offset = 0;
    if (_consider_phase)
      grn_index_offset = 1;

    //Assign center point values
    _centerpoints.resize(_grain_num);

    for (unsigned int gr = 0; gr < _grain_num; ++gr)
    {
      const EBSDReader::EBSDAvgData & d = _ebsd_reader.getAvgData(gr + grn_index_offset);
      _centerpoints[gr] = d.p;
    }

    // Assign grains to each order parameter in a way that maximizes distance
    _assigned_op.resize(_grain_num);

    _assigned_op = PolycrystalICTools::assignPointsToVariables(_centerpoints, _op_num, _mesh, _var);
  }
}

Real
ReconVarIC::value(const Point & /*p*/)
{
  // Initialize each point value by referencing the nodeToGrainWeightMap from the EBSDReader user object.
  // Import nodeToGrainWeightMap from EBSDReader for all nodes.  This map consists of the node index
  // followed by a vector of weights for all grains at that node.
  const std::map<dof_id_type, std::vector<Real> > & node_to_grn_weight_map = _ebsd_reader.getNodeToGrainWeightMap();

  // Return error if current node is NULL
  if (_current_node == NULL)
    mooseError("The following node id is reporting a NULL condition: " << _current_node->id());

  // Make sure the _current_node is in the node_to_grn_weight_map (return error if not in map)
  std::map<dof_id_type, std::vector<Real> >::const_iterator it = node_to_grn_weight_map.find(_current_node->id());

  if (it == node_to_grn_weight_map.end())
    mooseError("The following node id is not in the node map: " << _current_node->id());

  //Get local information from EBSDReader object
  EBSDReader::EBSDPointData local_ebsd_data; // = _ebsd_reader.getData(p);

  /*TODO: NEEDED FUNCTIONALITY THAT IS NOT CURRENTLY POSSIBLE
  //Output all grains in a specific phase to the same variable
  if (_all_to_one && _phase == local_ebsd_data.phase)
    return 1.0;
    */

  // Increment through all grains at node_index
  for (unsigned int grn = 0; grn < _grain_num; ++grn)
  {
    // If the current order parameter index (_op_index) is equal to the assinged index (_assigned_op),
    // set the value from node_to_grn_weight_map
    if (!_consider_phase)
      if (_assigned_op[grn] == _op_index && (it->second)[grn] > 0.0)
        return (it->second)[grn];
    //TODO: Make this work when considering phase
  }

  return 0.0;
}

