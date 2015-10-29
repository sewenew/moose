#
# Cavity Pressure Test
#
# This test is designed to compute an internal pressure based on
#   p = n * R * T / V
# where
#   p is the pressure
#   n is the amount of material in the volume (moles)
#   R is the universal gas constant
#   T is the temperature
#   V is the volume
#
# The mesh is composed of one block (2) with an interior cavity of volume 8.
#   Block 1 sits in the cavity and has a volume of 1.  Thus, the total
#   initial volume is 7.
# The test adjusts T in the following way:
#   T => T0 + beta*t
# with
#   beta = T0
#   T0 = 240.54443866068704
#   V0 = 7
#   n0 = f(p0)
#   p0 = 100
#   R = 8.314472 J* K^(−1)*mol^(−1)
#
# So, n0 = p0*V0/R/T0 = 100*7/8.314472/240.544439
#        = 0.35
#
# At t=1, p = 200.
#

[GlobalParams]
  disp_x = disp_x
  disp_y = disp_y
[]

[Problem]
  coord_type = RZ
[]

[Mesh]#Comment
  file = cavity_pressure_rz.e
[]

[Functions]
  [./temperature]
    type = PiecewiseLinear
    x = '0 1'
    y = '1 2'
    scale_factor = 240.54443866068704
  [../]
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

  [./temp]
    order = FIRST
    family = LAGRANGE
    initial_condition = 240.54443866068704
  [../]

[]

[SolidMechanics]
  [./solid]
    disp_r = disp_x
    disp_z = disp_y
  [../]
[]

[Kernels]

  [./heat]
    type = HeatConduction
    variable = temp
  [../]

[]

[BCs]

  [./no_x]
    type = DirichletBC
    variable = disp_x
    boundary = '1 2'
    value = 0.0
  [../]

  [./no_y]
    type = DirichletBC
    variable = disp_y
    boundary = '1 2'
    value = 0.0
  [../]

  [./temperatureInterior]
    type = FunctionDirichletBC
    boundary = 2
    function = temperature
    variable = temp
  [../]

  [./CavityPressure]
    [./1]
      boundary = 2
      initial_pressure = 100
      R = 8.314472
      temperature = aveTempInterior
      volume = internalVolume
      startup_time = 0.5
      output = ppress
    [../]
  [../]

[]

[Materials]

  [./stiffStuff]
    type = Elastic
    block = 1

    disp_r = disp_x
    disp_z = disp_y

    youngs_modulus = 1e6
    poissons_ratio = 0.3
    thermal_expansion = 0.0
  [../]

  [./stiffStuff2]
    type = Elastic
    block = 2

    disp_r = disp_x
    disp_z = disp_y

    youngs_modulus = 1e6
    poissons_ratio = 0.3
    thermal_expansion = 0.0
  [../]

  [./heatconduction]
    type = HeatConductionMaterial
    block = '1 2'
    thermal_conductivity = 1.0
    specific_heat = 1.0
  [../]

  [./density]
    type = Density
    block = '1 2'
    density = 1.0
    disp_r = disp_x
    disp_z = disp_y
  [../]
[]

[Executioner]

  type = Transient

  #Preconditioned JFNK (default)
  solve_type = 'PJFNK'



  petsc_options_iname = '-pc_type -sub_pc_type'
  petsc_options_value = 'asm       lu'

  nl_abs_tol = 1e-10

  l_max_its = 20

  start_time = 0.0
  dt = 0.5
  end_time = 1.0
[]

[Postprocessors]
  [./internalVolume]
    type = InternalVolume
    boundary = 2
    execute_on = 'initial linear'
  [../]

  [./aveTempInterior]
    type = SideAverageValue
    boundary = 2
    variable = temp
    execute_on = 'initial linear'
  [../]

[]

[Outputs]
  exodus = true
  [./checkpoint]
    type = Checkpoint
    num_files = 1
  [../]
[]
