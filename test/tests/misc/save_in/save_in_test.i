[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 2
  ny = 2
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./saved]
  [../]
  [./bc_saved]
  [../]
  [./accumulated]
  [../]
  [./diag_saved]
  [../]
  [./bc_diag_saved]
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
    save_in = 'saved accumulated'
    diag_save_in = diag_saved
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0
  [../]
  [./nbc]
    type = NeumannBC
    variable = u
    boundary = right
    value = 1
    save_in = 'bc_saved accumulated'
    diag_save_in = bc_diag_saved
  [../]
[]

[Postprocessors]
  [./left_flux]
    type = NodalSum
    variable = saved
    boundary = 1
  [../]
  [./saved_norm]
    type = NodalL2Norm
    variable = saved
    execute_on = timestep_end
    block = 0
  [../]
[]

[Executioner]
  type = Steady

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'

  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  file_base = out
  exodus = true
  output_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear linear'
  [../]
[]
