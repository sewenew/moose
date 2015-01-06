#
# Solving a fake thermo-mechanics problem
#
#

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
  nx = 10
  ny = 10
  elem_type = QUAD4
  displacements = 'disp_x disp_y'
[]

[Functions]
  [./temp_exact]
    type = ParsedFunction
    value = t*x
  [../]
  [./temp_ffn]
    type = ParsedFunction
    value = x
  [../]

  [./disp_x_exact]
    type = ParsedFunction
    value = (t*x)/5
  [../]
  [./disp_x_ffn]
    type = ParsedFunction
    value = x/5
  [../]

  [./disp_y_exact]
    type = ParsedFunction
    value = t*x*(y-0.5)/5
  [../]
  [./disp_y_ffn]
    type = ParsedFunction
    value = x*(y-0.5)/5
  [../]

[]

[Variables]
  [./temp]
  [../]

  [./disp_x]
  [../]
  [./disp_y]
  [../]
[]

[Kernels]
  # temp
  [./temp_td]
    type = TimeDerivative
    variable = temp
  [../]
  [./temp_diff]
    type = Diffusion
    variable = temp
  [../]
  [./temp_ffn]
    type = UserForcingFunction
    variable = temp
    function = temp_ffn
  [../]

  # disp_x
  [./disp_x_td]
    type = TimeDerivative
    variable = disp_x
    use_displaced_mesh = true
  [../]
  [./disp_x_diff]
    type = Diffusion
    variable = disp_x
    use_displaced_mesh = true
  [../]
  [./disp_x_ffn]
    type = UserForcingFunction
    variable = disp_x
    function = disp_x_ffn
    use_displaced_mesh = true
  [../]

  # disp_y
  [./disp_y_td]
    type = TimeDerivative
    variable = disp_y
  [../]
  [./disp_y_diff]
    type = Diffusion
    variable = disp_y
    use_displaced_mesh = true
  [../]
  [./disp_y_ffn]
    type = UserForcingFunction
    variable = disp_y
    function = disp_y_ffn
  [../]
[]

[BCs]
  [./temp_all]
    type = FunctionDirichletBC
    variable = temp
    boundary = '0 1 2 3'
    function = temp_exact
  [../]

  [./disp_x_all]
    type = FunctionDirichletBC
    variable = disp_x
    boundary = '0 1 2 3'
    function = disp_x_exact
  [../]

  [./disp_y_all]
    type = FunctionDirichletBC
    variable = disp_y
    boundary = '0 1 2 3'
    function = disp_y_exact
  [../]
[]

[Executioner]
  type = Transient
  start_time = 0
  dt = 0.1
  num_steps = 5
[]

[Outputs]
  exodus = true
  output_on = 'initial timestep_end'
[]
