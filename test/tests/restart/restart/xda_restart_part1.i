# We run a simple problem (5 time steps and save off the solution)
# In part2, we load the solution and solve a steady problem. The test check, that the initial state in part 2 is the same as the last state from part1

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = -1
  xmax = 1
  ymin = -1
  ymax = 1
  nx = 10
  ny = 10
[]

[Functions]
  [./exact_fn]
    type = ParsedFunction
    value = t*((x*x)+(y*y))
  [../]

  [./forcing_fn]
    type = ParsedFunction
    value = -4+(x*x+y*y)
  [../]
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]

  [./diffusivity]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./ie]
    type = TimeDerivative
    variable = u
  [../]

  [./diff]
    type = MatDiffusion
    variable = u
    prop_name = diffusivity
  [../]

  [./ffn]
    type = UserForcingFunction
    variable = u
    function = forcing_fn
  [../]

  [./out_diffusivity]
    type = RealPropertyOutput
    variable = diffusivity
    prop_name = diffusivity
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = u
    boundary = '0 1 2 3'
    function = exact_fn
  [../]
[]

[Materials]
  [./mat]
    type = StatefulMaterial
    block = 0
    initial_diffusivity = 0.5
  [../]
[]

[Executioner]
  type = Transient

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'

  dt = 0.2
  start_time = 0
  num_steps = 5
[]

[Outputs]
  file_base = out_xda_restart_part1
  exodus = true
  checkpoint = true
  output_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear'
  [../]
[]
