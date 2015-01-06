/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef OUTPUTWAREHOUSE_H
#define OUTPUTWAREHOUSE_H

// Standard includes
#include <vector>

// MOOSE includes
#include "Warehouse.h"
#include "InputParameters.h"

// Forward declarations
class Output;
class Checkpoint;
class FEProblem;

/**
 * Class for storing and utilizing output objects
 */
class OutputWarehouse : public Warehouse<Output>
{
public:

  /**
   * Class constructor
   */
  OutputWarehouse();

  /*
   * Class destructor
   * The OutputWarehouse deletes all output objects passed in via addOutput
   */
  virtual ~OutputWarehouse();

  /**
   * Adds an existing output object to the warehouse
   * @param output Pointer to the output object
   * It is the responsibility of the OutputWarehouse to delete the output objects
   * add using this method
   */
  void addOutput(MooseSharedPointer<Output> & output);

  /**
   * Get a complete list of all output objects
   * @return A vector of pointers to each of the output objects
   */
  const std::vector<Output *> & getOutputs() const;

  /**
   * Get a complete set of all output object names
   * @return A set of output names for each output object
   */
  const std::set<OutputName> & getOutputNames() const;

  /**
   * Returns true if the output object exists
   * @param name The name of the output object for which to test for existence within the warehouse
   */
  bool hasOutput(const std::string & name) const;

  /**
   * Calls the outputStep method for each output object
   * @param type The type execution flag (see Moose.h)
   */
  void outputStep(ExecFlagType type);

  /**
   * Calls the meshChanged method for every output object
   */
  void meshChanged();

  /**
   * Return the list of hidden variables for the given output name
   * @param output_name The name of the output object for which the variables should be returned
   * @param hide The set of variables to hide which is built by this method
   *
   * Objects inheriting from the OutputInterface have the ability to control the output of variables
   * associated with the objects (i.e., Marker elemental variable). This method returns a list
   * of variables that should be hidden for the supplied object name due to the 'outputs' parameter
   * being set by the object(s).
   *
   * This method is used by Output::initOutputList to populate the correct hide lists for the
   * output object, it is not intended for general use.
   */
  void buildInterfaceHideVariables(const std::string & output_name, std::set<std::string> & hide);

  /**
   * Calls the setFileNumber method for every FileOutput output object
   */
  void setFileNumbers(std::map<std::string, unsigned int> input, unsigned int offset = 0);

  /**
   * Extracts the file numbers from the output objects
   * @return Map of file numbers for the output objects
   */
  std::map<std::string, unsigned int> getFileNumbers();

  /**
   * Stores the common InputParameters object
   * @param params_ptr A pointer to the common parameters object to be stored
   *
   * @see CommonOutputAction
   */
  void setCommonParameters(InputParameters * params_ptr);

  /**
   * Get a reference to the common output parameters
   * @return Pointer to the common InputParameters object
   */
  InputParameters * getCommonParameters();

  /**
   * Return the sync times for all objects
   */
  std::set<Real> & getSyncTimes();

  /**
   * Call the init() method for each of the Outputs
   */
  void init();

  /**
   * Test that the output names exist
   * @param A vector of names to check
   * This method will produce an error if any of the supplied
   * names do not exist in the warehouse. Reserved names are not considered.
   */
  void checkOutputs(const std::set<OutputName> & names);

  /**
   * Return an Output object by name
   * @tparam T The Output object type to return
   * @param The name of the output object
   * @return A pointer to the output object
   */
  template<typename T>
  T * getOutput(const OutputName & name);

  /**
   * Return a vector of objects by names
   * @tparam T The Output object type to return
   * @param names A vector of names of the output object
   * @return A pointer to the output object
   */
  template<typename T>
  std::vector<T *> getOutputs(const std::vector<OutputName> & names);

  /**
   * Return a vector of objects of a given type
   * @tparam T The Output object type to return
   * @return A pointer to the output object
   */
  template<typename T>
  std::vector<T *> getOutputs() const;

  /**
   * Return a list of output objects with a given type
   * @tparam T The output object type
   * @return A vector of names
   */
  template<typename T>
  std::vector<OutputName> getOutputNames();

  /**
   * Return a set of reserved output names
   * @return A std::set of reserved names
   */
  const std::set<std::string> & getReservedNames() const;

  /**
   * Test if the given name is reserved
   * @param name The name to test
   * @return True if the name is reserved
   */
  bool isReservedName(const std::string & name);

  /**
   * Sends the supplied message to Console output objects
   * @param message A string containing the message to write
   */
  void mooseConsole();

  /**
   * The multiapp level
   * @return A writable reference to the current number of levels from the master app
   */
  unsigned int & multiappLevel() { return _multiapp_level; }

  /**
   * The buffered messages stream for Console objectsc
   * @return Reference to the stream storing cached messages from calls to _console
   */
  std::ostringstream & consoleBuffer() { return _console_buffer; }

  /**
   * Ability to enable/disable all output calls
   *
   * This is needed by RattleSNake/YAK to disable output because of the Yo Dawg executioners calling
   * other executioners.
   */
  void allowOutput(bool state);

  /**
   * Indicates that the next call to outputStep should be forced
   *
   * This is needed by the MultiApp system, if forceOutput is called the next call to outputStep,
   * regardless of the type supplied to the call, will be executed with EXEC_FORCED.
   *
   * Forced output will NOT override the allowOutput flag
   */
  void forceOutput();

private:
  /**
   * We are using MooseSharedPointer to handle the cleanup of the pointers at the end of execution.
   * This is necessary since several warehouses might be sharing a single instance of a MooseObject.
   */
  std::vector<MooseSharedPointer<Output> > _all_ptrs;

  /**
   * Adds the file name to the list of filenames being output
   * The main function of this object is to test that the same output file
   * does not already exist to protect against output files overwriting each other
   * @param ptr Pointer to the Output object
   * @param filename Name of an output file (extracted from filename() method of the objects)
   */
  void addOutputFilename(const OutFileBase & filename);

  /**
   * Calls the initialSetup function for each of the output objects
   * @see FEProblem::initialSetup()
   */
  void initialSetup();

  /**
   * Calls the timestepSetup function for each of the output objects
   * @see FEProblem::timestepSetup()
   */
  void timestepSetup();

  /**
   * Calls the jacobianSetup function for each of the output objects
   * @see FEProblem::computeJacobian
   */
  void jacobianSetup();

  /**
   * Calls the residualSetup function for each of the output objects
   * @see FEProblem::computeResidualTyp
   */
  void residualSetup();

  /**
   * Calls the subdomainSetup function for each of the output objects
   * @see FEProblem::setupSubdomain
   */
  void subdomainSetup();

  /**
   * Insert a variable name for hiding via the OutoutInterface
   * @param output_name The name of the output object on which the variable is to be hidden
   * @param variable_name The name of the variable to be hidden
   *
   * This is a private method used by the OutputInterface system, it is not intended for any
   * other purpose.
   */
  void addInterfaceHideVariables(const std::string & output_name, const std::set<std::string> & variable_names);

  /**
   * Sets the execution flag type
   *
   * This is a private method used by FEProblem, it is not intended for any other purpose
   */
  void setOutputExecutionType(ExecFlagType type);

  /// A map of the output pointers
  std::map<OutputName, Output *> _object_map;

  /// A set of output names
  std::set<OutputName> _object_names;

  /// List of object names
  std::set<OutFileBase> _file_base_set;

  /// Pointer to the common InputParameters (@see CommonOutputAction)
  InputParameters * _common_params_ptr;

  /// Sync times for all objects
  std::set<Real> _sync_times;

  /// Input file name for this output object
  std::string _input_file_name;

  /// Map of output name and AuxVariable names to be output (used by auto Material output)
  std::map<OutputName, std::set<AuxVariableName> > _material_output_map;

  /// List of all variable created by auto material output
  std::set<AuxVariableName> _all_material_output_variables;

  /// List of reserved names
  std::set<std::string> _reserved;

  /// Level of multiapp, the master is level 0. This used by the Console to indent output
  unsigned int _multiapp_level;

  /// Stream for holding messages passed to _console prior to Output object construction
  std::ostringstream _console_buffer;

  /// Storage for variables to hide as prescribed by the object via the OutputInterface
  std::map<std::string, std::set<std::string> > _interface_map;

  /// The current output execution flag
  ExecFlagType _output_exec_flag;

  /// Flag for enabling/disabling all output
  bool _allow_output;

  /// Flag indicating that next call to outputStep is forced
  bool _force_output;

  // Allow complete access:
  //  (1) FEProblem for calling initial/timestepSetup functions
  //  (2) MaterialOutputAction for calling addInterfaceHideVariables
  //  (3) OutputInterface for calling addInterfaceHideVariables
  friend class FEProblem;
  friend class MaterialOutputAction;
  friend class OutputInterface;
};

template<typename T>
T *
OutputWarehouse::getOutput(const OutputName & name)
{
  // Check that the object exists
  if (!hasOutput(name))
    mooseError("An output object with the name '" << name << "' does not exist.");

  // Attempt to cast the object to the correct type
  T * output = dynamic_cast<T*>(_object_map[name]);

  // Error if the cast fails
  if (output == NULL)
    mooseError("An output object with the name '" << name << "' for the specified type does not exist");

  // Return the object
  return output;
}

template<typename T>
std::vector<T *>
OutputWarehouse::getOutputs(const std::vector<OutputName> & names)
{
  // The vector to output
  std::vector<T *> outputs;

  // Populate the vector
  for (std::vector<OutputName>::const_iterator it = names.begin(); it != names.end(); ++it)
    outputs.push_back(getOutput<T>(*it));

  // Return the objects
  return outputs;
}

template<typename T>
std::vector<T *>
OutputWarehouse::getOutputs() const
{
  // The vector to output
  std::vector<T *> outputs;

  // Populate the vector
  for (std::map<OutputName, Output *>::const_iterator it = _object_map.begin(); it != _object_map.end(); ++it)
  {
    T * output = dynamic_cast<T*>(it->second);
    if (output != NULL)
      outputs.push_back(output);
  }

  // Return the objects
  return outputs;
}

/**
 * Return a list of output objects with a given type
 * @tparam T The output object type
 * @return A vector of names
 */
template<typename T>
std::vector<OutputName>
OutputWarehouse::getOutputNames()
{
  // The output vector
  std::vector<OutputName> names;

  // Loop through the objects and store the name if the type cast succeeds
  for (std::map<OutputName, Output *>::const_iterator it = _object_map.begin(); it != _object_map.end(); ++it)
  {
    T * output = dynamic_cast<T*>(it->second);
    if (output != NULL)
      names.push_back(it->first);
  }

  // Return the names
  return names;
}

#endif // OUTPUTWAREHOUSE_H
