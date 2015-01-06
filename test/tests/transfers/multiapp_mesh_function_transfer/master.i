[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  # The MultiAppMeshFunctionTransfer doesn't work with ParallelMesh.
  # See tosub_master.i and #2145 for more information.
  distribution = serial
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./transferred_u]
  [../]
  [./elemental_transferred_u]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 1
  dt = 1

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'

  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
  output_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear linear'
  [../]
[]

[MultiApps]
  [./sub]
    positions = '.099 .099 0 .599 .599 0 0.599 0.099 0'
    type = TransientMultiApp
    app_type = MooseTestApp
    input_files = sub.i
  [../]
[]

[Transfers]
  [./from_sub]
    source_variable = sub_u
    direction = from_multiapp
    variable = transferred_u
    type = MultiAppMeshFunctionTransfer
    multi_app = sub
  [../]
  [./elemental_from_sub]
    source_variable = sub_u
    direction = from_multiapp
    variable = elemental_transferred_u
    type = MultiAppMeshFunctionTransfer
    multi_app = sub
  [../]
[]
