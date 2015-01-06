[Mesh]
  file = gold/rd02.e
[]


[GlobalParams]
  richardsVarNames_UO = PPNames
[]

[UserObjects]
  [./PPNames]
    type = RichardsVarNames
    richards_vars = pressure
  [../]
  [./DensityConstBulk]
    type = RichardsDensityConstBulk
    dens0 = 1E3
    bulk_mod = 2E7
  [../]
  [./SeffVG]
    type = RichardsSeff1VG
    m = 0.336
    al = 1.43E-4 # same deal with PETSc's "constant state"
  [../]
  [./RelPermPower]
    type = RichardsRelPermVG1
    scut = 0.99
    simm = 0.0
    m = 0.336
  [../]
  [./Saturation]
    type = RichardsSat
    s_res = 0.0
    sum_s_res = 0.0
  [../]
  [./SUPGstandard]
    type = RichardsSUPGstandard
    p_SUPG = 1.0E+0
  [../]
[]



[Variables]
  active = 'pressure'
  [./pressure]
    order = FIRST
    family = LAGRANGE
    initial_from_file_timestep = 2
    initial_from_file_var = pressure
  [../]
[]


[Kernels]
  active = 'richardsf richardst'
  [./richardst]
    type = RichardsMassChange
    variable = pressure
  [../]
  [./richardsf]
    type = RichardsFlux
    variable = pressure
  [../]
[]


[AuxVariables]
  [./Seff1VG_Aux]
  [../]
[]


[AuxKernels]
  [./Seff1VG_AuxK]
    type = RichardsSeffAux
    variable = Seff1VG_Aux
    seff_UO = SeffVG
    pressure_vars = pressure
  [../]
[]




[BCs]
  active = 'fix_bot'
  [./fix_bot]
    type = DirichletBC
    variable = pressure
    boundary = 'left'
    value = 0.0
  [../]
[]


[Materials]
  [./rock]
    type = RichardsMaterial
    block = 0
    mat_porosity = 0.33
    mat_permeability = '0.295E-12 0 0  0 0.295E-12 0  0 0 0.295E-12'
    density_UO = DensityConstBulk
    relperm_UO = RelPermPower
    SUPG_UO = SUPGstandard
    sat_UO = Saturation
    seff_UO = SeffVG
    viscosity = 1.01E-3
    gravity = '-10 0 0'
    linear_shape_fcns = true
  [../]
[]

#[Adaptivity]
#  marker = errorfrac
#  max_h_level = 3
#  [./Indicators]
#    [./error]
#      type = RichardsFluxJumpIndicator
#      variable = pressure
#    [../]
#  [../]
#  [./Markers]
#    [./errorfrac]
#      type = ErrorFractionMarker
#      refine = 0.5
#      coarsen = 0.3
#      indicator = error
#   [../]
#  [../]
#[]

[Preconditioning]
  active = 'andy'

  [./andy]
    type = SMP
    full = true
    petsc_options = ''

    petsc_options_iname = '-ksp_type -pc_type -snes_atol -snes_rtol -snes_max_it'
    petsc_options_value = 'bcgs bjacobi 1E-13 1E-15 10000'
  [../]
[]


[Executioner]
  type = Transient
  solve_type = Newton
  petsc_options = '-snes_converged_reason'
  end_time = 8.2944E6

  [./TimeStepper]
    type = FunctionDT
    time_dt = '2E4 1E6'
    time_t = '0 1E6'
  [../]


#  [./TimeStepper]
#    type = FunctionControlledDT
#    functions = ''
#    maximums = ''
#    minimums = ''
#    dt = 1e-2
#    increment = 1.1
#    decrement = 0.5
#    maxDt = 1E12
#    minDt = 1
#    adapt_log = false
#    percent_change = 0.1
#  [../]
[]


[Outputs]
  file_base = rd03
  interval = 100000
  exodus = true
  output_on = 'initial timestep_end final'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear'
  [../]
[]
