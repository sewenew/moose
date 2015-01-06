[Mesh]
  file = elem_map.e
  # The SolutionUserObject uses the copy_nodal_solution() capability
  # of the Exodus reader, and therefore won't work if the initial mesh
  # has been renumbered (it will be reunumbered if you are running with
  # ParallelMesh in parallel).  Hence, we restrict this test to run with
  # SerialMesh only.
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
  [./matid]
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

[AuxKernels]
  [./matid]
    type = SolutionAux
    solution = soln
    variable = matid
    scale_factor = 1.0
  [../]
[]

[UserObjects]
  [./soln]
    type = SolutionUserObject
    mesh = elem_map.e
    system_variables = MatID
    timestep = 1
  [../]
[]

[BCs]
  [./stuff]
    type = DirichletBC
    variable = u
    boundary = '1'
    value = 1.0
  [../]
[]

[Executioner]
  type = Steady

  solve_type = 'PJFNK'
[]

[Outputs]
  exodus = true
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear'
  [../]
[]
