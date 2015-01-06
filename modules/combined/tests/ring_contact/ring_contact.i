#
# A test of contact with quadratic (Hex20) elements
#
# A stiff ring is pushed into a soft base.  The base shows a circular impression.
#

[GlobalParams]
  order = SECOND
  family = LAGRANGE
[]


[Mesh]
  file = ring_contact.e
  displacements = 'disp_x disp_y disp_z'
[]

[Variables]
  [./disp_x]
  [../]

  [./disp_y]
  [../]

  [./disp_z]
  [../]
[] # Variables

[Functions]
  [./ring_y]
    type = PiecewiseLinear
    x = '0 1'
    y = '0 1'
    scale_factor = -0.2
  [../]
[]

[SolidMechanics]
  [./solid]
    disp_x = disp_x
    disp_y = disp_y
    disp_z = disp_z
  [../]
[]

[Contact]
  [./dummy_name]
    master = 3
    slave = 2
    disp_x = disp_x
    disp_y = disp_y
    disp_z = disp_z
    penalty = 1e3
    tension_release = -1
  [../]
[]

[BCs]
  [./plane]
    type = PresetBC
    variable = disp_z
    boundary = 10
    value = 0.0
  [../]

  [./bottom_x]
    type = PresetBC
    variable = disp_x
    boundary = 1
    value = 0.0
  [../]

  [./bottom_y]
    type = PresetBC
    variable = disp_y
    boundary = 1
    value = 0.0
  [../]

  [./bottom_z]
    type = PresetBC
    variable = disp_z
    boundary = 1
    value = 0.0
  [../]

  [./ring_x]
    type = PresetBC
    variable = disp_x
    boundary = 4
    value = 0.0
  [../]

  [./ring_y]
    type = FunctionPresetBC
    variable = disp_y
    boundary = 4
    function = ring_y
  [../]

[] # BCs

[Materials]

  [./stiffStuff1]
    type = Elastic
    block = 1

    disp_x = disp_x
    disp_y = disp_y
    disp_z = disp_z

    youngs_modulus = 1e6
    poissons_ratio = 0.3
  [../]
  [./stiffStuff2]
    type = Elastic
    block = 2

    disp_x = disp_x
    disp_y = disp_y
    disp_z = disp_z

    youngs_modulus = 1e3
    poissons_ratio = 0.3
  [../]
[] # Materials

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  []
[]

[Executioner]
  type = Transient

  #Preconditioned JFNK (default)
  solve_type = 'PJFNK'



#  petsc_options_iname = '-pc_type -pc_hypre_type -snes_type -snes_ls -snes_linesearch_type -ksp_gmres_restart'
#  petsc_options_value = 'hypre    boomeramg      ls         basic    basic                    101'
  petsc_options_iname = '-pc_type -ksp_gmres_restart'
  petsc_options_value = 'lu       101'


  line_search = 'none'


  nl_abs_tol = 1e-8

  l_max_its = 100
  nl_max_its = 10
  dt = 0.1
  end_time = 0.5
  num_steps = 100

  [./Quadrature]
    order = THIRD
  [../]

[] # Executioner

[Outputs]
  file_base = out
  exodus = true
  output_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear linear'
  [../]
[] # Outputs
