[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = -1
  xmax = 1
  nx = 5
  elem_type = EDGE3
[]

[Functions]
  [./bc_fnl]
    type = ParsedFunction
    value = -1
  [../]
  [./bc_fnr]
    type = ParsedFunction
    value = 1
  [../]

  [./forcing_fn]
    type = ParsedFunction
    value = x
  [../]

  [./solution]
    type = ParsedGradFunction
    value = x
    grad_x = 1
[]

[Variables]
  [./u]
    order = FIRST
    family = HIERARCHIC
  [../]
[]

[Kernels]
  active = 'diff forcing reaction'
  [./diff]
    type = Diffusion
    variable = u
  [../]

  [./reaction]
    type = Reaction
    variable = u
  [../]

  [./forcing]
    type = UserForcingFunction
    variable = u
    function = forcing_fn
  [../]
[]

[BCs]
  [./bc_left]
    type = FunctionNeumannBC
    variable = u
    boundary = 'left'
    function = bc_fnl
  [../]
  [./bc_right]
    type = FunctionNeumannBC
    variable = u
    boundary = 'right'
    function = bc_fnr
  [../]
[]

[Postprocessors]
  [./dofs]
    type = NumDOFs
  [../]

  [./h]
    type = AverageElementSize
    variable = u
  [../]

  [./L2error]
    type = ElementL2Error
    variable = u
    function = solution
  [../]
  [./H1error]
    type = ElementH1Error
    variable = u
    function = solution
  [../]
  [./H1Semierror]
    type = ElementH1SemiError
    variable = u
    function = solution
  [../]
[]

[Executioner]
  type = Steady
  nl_rel_tol = 1e-11

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'
[]

[Outputs]
  exodus = true
  csv = true
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear'
  [../]
[]
