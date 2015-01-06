[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  xmax = 10
  ymin = 0
  ymax = 10
  nx = 10
  ny = 10
[]

[Variables]
  active = 'u prop1'

  [./u]
    order = FIRST
    family = LAGRANGE
  [../]

  [./prop1]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  active = 'heat ie prop1_output'

  [./heat]
    type = MatDiffusion
    variable = u
    prop_name = thermal_conductivity
  [../]

  [./ie]
    type = TimeDerivative
    variable = u
  [../]

  [./prop1_output]
    type = RealPropertyOutput
    variable = prop1
    prop_name = thermal_conductivity
  [../]
[]

[BCs]
  active = 'left right'

  [./left]
    type = DirichletBC
    variable = u
    boundary = 3
    value = 0.0
  [../]

  [./right]
    type = MTBC
    variable = u
    boundary = 1
    grad = 1.0
    prop_name = thermal_conductivity
  [../]
[]

[Materials]
  active = 'stateful'

  [./stateful]
    type = StatefulSpatialTest
    block = 0
  [../]
[]

[Executioner]
  type = Transient

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'

  start_time = 0.0
  num_steps = 5
  dt = .1
[]

[Outputs]
  file_base = out_spatial
  exodus = true
  output_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear'
  [../]
[]
