[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 25
  ny = 25
  nz = 0
  xmax = 250
  ymax = 250
  zmax = 0
  elem_type = QUAD4
[]

[Variables]
  [./disp_x]
    order = FIRST
    family = LAGRANGE
  [../]
  [./disp_y]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./c]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = SmoothCircleIC
      x1 = 125.0
      y1 = 125.0
      radius = 60.0
      invalue = 1.0
      outvalue = 0.1
      int_width = 50.0
    [../]
  [../]
  [./e11_aux]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./stress_e11]
    type = RankTwoAux
    rank_two_tensor = stress
    index_i = 0
    index_j = 0
    variable = e11_aux
  [../]
[]

[BCs]
  [./bottom]
    type = PresetBC
    boundary = bottom
    variable = disp_y
    value = 0.
  [../]
  [./left]
    type = PresetBC
    boundary = left
    variable = disp_x
    value = 0.
  [../]
[]

[Kernels]
  [./TensorMechanics]
    disp_x = disp_x
    disp_y = disp_y
  [../]
[]

[Materials]
  [./eigenstrain]
    type = SimpleEigenStrainMaterial
    block = 0
    epsilon0 = 0.05
    c = c
    disp_y = disp_y
    disp_x = disp_x
    C_ijkl = '3 1 1 3 1 3 1 1 1 '
    fill_method = symmetric9
  [../]
[]

[Executioner]
  type = Transient
  solve_type = 'PJFNK'
  nl_abs_tol = 1e-10
  num_steps = 1
[]

[Outputs]
  exodus = true
  output_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear'
  [../]
[]
