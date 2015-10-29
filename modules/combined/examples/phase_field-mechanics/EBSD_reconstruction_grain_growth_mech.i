# This example reconstructs the grain structure from an EBSD data file
# Then, an isotropic grain model is run with linear elasticity and an anisotropic
# elasticity tensor that uses the measured EBSD angles.
[Mesh]
  uniform_refine = 2 #Mesh can go two levels coarser than the EBSD grid
  type = EBSDMesh
  filename = IN100_128x128.txt
[]

[GlobalParams]
  op_num = 30
  var_name_base = gr
  grain_num = 110
[]

[Variables]
  [./PolycrystalVariables] #Polycrystal variable generation (30 order parameters)
  [../]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
[]

[AuxVariables]
  [./bnds]
  [../]
  [./gt_indices]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./unique_grains]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./T]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 500
  [../]
  [./vonmises_stress]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./C1111]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./phi1]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Phi]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./phi2]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[ICs]
  [./PolycrystalICs]
    [./ReconVarIC]
      ebsd_reader = ebsd
      consider_phase = false
    [../]
  [../]
[]

[Kernels]
  [./PolycrystalKernel]
  [../]
  [./PolycrystalElasticDrivingForce]
  [../]
  [./TensorMechanics]
    displacements = 'disp_x disp_y'
  [../]
[]

[AuxKernels]
  [./BndsCalc]
    type = BndsCalcAux
    variable = bnds
    execute_on = 'initial timestep_end'
  [../]
  [./gt_indices]
    type = FeatureFloodCountAux
    variable = gt_indices
    execute_on = 'initial timestep_end'
    bubble_object = grain_tracker
    field_display = VARIABLE_COLORING
  [../]
  [./unique_grains]
    type = FeatureFloodCountAux
    variable = unique_grains
    execute_on = 'initial timestep_end'
    bubble_object = grain_tracker
    field_display = UNIQUE_REGION
  [../]
  [./C1111]
    type = RankFourAux
    variable = C1111
    rank_four_tensor = elasticity_tensor
    index_l = 0
    index_j = 0
    index_k = 0
    index_i = 0
    execute_on = timestep_end
  [../]
  [./vonmises_stress]
    type = RankTwoScalarAux
    variable = vonmises_stress
    rank_two_tensor = stress
    scalar_type = VonMisesStress
    execute_on = timestep_end
  [../]
  [./phi1]
    type = OutputEulerAngles
    variable = phi1
    euler_angle_provider = ebsd
    GrainTracker_object = grain_tracker
    output_euler_angle = 'phi1'
    execute_on = 'initial'
  [../]
  [./Phi]
    type = OutputEulerAngles
    variable = Phi
    euler_angle_provider = ebsd
    GrainTracker_object = grain_tracker
    output_euler_angle = 'Phi'
    execute_on = 'initial'
  [../]
  [./phi2]
    type = OutputEulerAngles
    variable = phi2
    euler_angle_provider = ebsd
    GrainTracker_object = grain_tracker
    output_euler_angle = 'phi2'
    execute_on = 'initial'
  [../]
[]

[BCs]
  [./top_displacement]
    type = PresetBC
    variable = disp_y
    boundary = top
    value = -2.0
  [../]
  [./x_anchor]
    type = PresetBC
    variable = disp_x
    boundary = 'left right'
    value = 0.0
  [../]
  [./y_anchor]
    type = PresetBC
    variable = disp_y
    boundary = bottom
    value = 0.0
  [../]
[]

[Materials]
  [./Copper]
    # T = 500 # K
    type = GBEvolution
    block = 0
    T = T
    wGB = 0.6 # um
    GBmob0 = 2.5e-6 # m^4/(Js) from Schoenfelder 1997
    Q = 0.23 # Migration energy in eV
    GBenergy = 0.708 # GB energy in J/m^2
    molar_volume = 7.11e-6; # Molar volume in m^3/mol
    length_scale = 1.0e-6
    time_scale = 1.0e-6
  [../]
  [./ElasticityTensor]
    type = ComputePolycrystalElasticityTensor
    block = 0
    fill_method = symmetric9
    #reading C_11  C_12  C_13  C_22  C_23  C_33  C_44  C_55  C_66
    Elastic_constants = '1.27e5 0.708e5 0.708e5 1.27e5 0.708e5 1.27e5 0.7355e5 0.7355e5 0.7355e5'
    GrainTracker_object = grain_tracker
    euler_angle_provider = ebsd
  [../]
  [./strain]
    type = ComputeSmallStrain
    block = 0
    displacements = 'disp_x disp_y'
  [../]
  [./stress]
    type = ComputeLinearElasticStress
    block = 0
  [../]
[]

[Postprocessors]
  [./dt]
    type = TimestepSize
  [../]
  [./n_elements]
    type = NumElems
    execute_on = 'initial timestep_end'
  [../]
  [./n_nodes]
    type = NumNodes
    execute_on = 'initial timestep_end'
  [../]
  [./DOFs]
    type = NumDOFs
  [../]
[]

[UserObjects]
  [./ebsd]
    type = EBSDReader
  [../]
  [./grain_tracker]
    type = GrainTracker
    threshold = 0.1
    convex_hull_buffer = 0
    use_single_map = false
    enable_var_coloring = true
    condense_map_info = true
    compute_op_maps = true
    bubble_volume_file = IN100-grn-vols.txt
    execute_on = 'initial timestep_begin'
    ebsd_reader = ebsd
    flood_entity_type = ELEMENTAL
  [../]
[]

[Executioner]
  type = Transient
  scheme = bdf2
  solve_type = PJFNK # Preconditioned JFNK (default)
  petsc_options_iname = '-pc_type -pc_hypre_type -pc_hypre_boomeramg_strong_threshold'
  petsc_options_value = '  hypre    boomeramg                   0.7'
  l_tol = 1.0e-4
  l_max_its = 20
  nl_max_its = 20
  nl_rel_tol = 1.0e-8
  start_time = 0.0
  num_steps = 30
  dt = 10
  [./Adaptivity]
    initial_adaptivity = 0
    refine_fraction = 0.7
    coarsen_fraction = 0.1
    max_h_level = 2
  [../]
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.9
    dt = 10.0
    growth_factor = 1.1
    optimal_iterations = 7
  [../]
[]

[Outputs]
  csv = true
  exodus = true
[]
