[Mesh]
  # This test uses SolutionUserObject which doesn't work with ParallelMesh.
  type = FileMesh
  file = cubesource.e
  distribution = serial
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0.0
  [../]
[]

[AuxVariables]
  [./nn]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[AuxKernels]
  [./nn]
    type = SolutionAux
    variable = nn
    solution = soln
  [../]
[]

[UserObjects]
  [./soln]
    type = SolutionUserObject
    mesh = cubesource.e
    system_variables = source_nodal
  [../]
[]

[BCs]
  [./stuff]
    type = DirichletBC
    variable = u
    boundary = '1 2'
    value = 0.0
  [../]
[]

[Executioner]
  type = Transient
  restart_file_base = solution_aux_exodus_interp_restart1_out_cp/0005
  solve_type = NEWTON
  l_max_its = 800
  nl_rel_tol = 1e-10
  num_steps = 10
  end_time = 5
  dt = 0.5
[]

[Outputs]
  exodus = true
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear'
  [../]
[]
