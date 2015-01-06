[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 10
  ny = 10
  uniform_refine = 1
[]

[Variables]
  [./u]
  [../]
[]

[Kernels]
  [./fddiff]
    type = FDDiffusion
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
  type = Steady

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'

  petsc_options       = 'snes_view'
  petsc_options_iname = '-pc_type'
  petsc_options_value = '      lu'
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

[Debug]
  show_var_residual_norms = true
[]
