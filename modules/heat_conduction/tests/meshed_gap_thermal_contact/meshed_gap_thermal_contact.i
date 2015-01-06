[Mesh]
  type = FileMesh
  file = meshed_gap.e
  dim = 2
[]

[Variables]
  [./temp]
    block = '1 3'
  [../]
[]

[Kernels]
  [./hc]
    type = HeatConduction
    variable = temp
    block = '1 3'
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = temp
    boundary = 1
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = temp
    boundary = 4
    value = 1
  [../]
[]

[ThermalContact]
  [./gap_conductivity]
    type = GapHeatTransfer
    variable = temp
    master = 2
    slave = 3
    gap_conductivity = 0.5
  [../]
[]

[Materials]
  [./hcm]
    type = HeatConductionMaterial
    block = '1 2 3'
    temp = temp
    thermal_conductivity = 1
  [../]
[]

[Problem]
  type = FEProblem
  kernel_coverage_check = false
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Steady
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  output_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear linear'
  [../]
  [./out]
    type = Exodus
  [../]
[]
