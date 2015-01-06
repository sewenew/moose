#
# 1-D Gap Heat Transfer Test without mechanics
#
# This test exercises 1-D gap heat transfer for a constant conductivity gap.
#
# The mesh consists of two element blocks with a mesh biased toward the gap
#   between them.  Each block is unit length.  The gap between them is one
#   unit in length.
#
# The conductivity of both blocks is set very large to achieve a uniform temperature
#  across each block. The temperature of the far left boundary
#  is ramped from 100 to 200 over one time unit, and then held fixed for an additional
#  time unit.  The temperature of the far right boundary is held fixed at 100.
#
# A simple analytical solution is possible for the heat flux between the blocks
#  (Note that this is for a Cartesion system, and the equation for a cylindrical
#   system is different.  What is given here matches what is coded.):
#
#  Flux = (T_left - T_right) * (gapK/gap_width)
#
# The gap conductivity is specified as 1, thus
#
#  gapK = 1.0
#
# The integrated heat flux across the gap at time = 2 is then:
#
#  IntegrFlux(2) = Area * 100 * (1.0/1.0) = Area * 100
#
#  The area is taken as the area of the slave (inner) surface:
#
#  Area = 4 * pi * 1 * 1
#
#  So,
#
#  IntegrFlux(2) = 4 * pi * 100 -> 1256.64
#
# For comparison, see results from the flux post processors
#

[Problem]
  coord_type = RSPHERICAL
[]

[Mesh]
  file = gap_heat_transfer_htonly_rspherical.e
  construct_side_list_from_node_list = true
[]

[Functions]

  [./temp]
    type = PiecewiseLinear
    x = '0   1   2'
    y = '100 200 200'
  [../]
[]

[ThermalContact]
  [./thermal_contact]
    type = GapHeatTransfer
    variable = temp
    master = 3
    slave = 2
  [../]
[]

[Variables]
  [./temp]
    order = FIRST
    family = LAGRANGE
    initial_condition = 100
  [../]
[]

[AuxVariables]
  [./gap_cond]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  [./heat]
    type = HeatConduction
    variable = temp
  [../]
[]


[BCs]
  [./temp_far_left]
    type = FunctionPresetBC
    boundary = 1
    variable = temp
    function = temp
  [../]

  [./temp_far_right]
    type = PresetBC
    boundary = 4
    variable = temp
    value = 100
  [../]
[]

[AuxKernels]
  [./conductance]
    type = MaterialRealAux
    property = gap_conductance
    variable = gap_cond
    boundary = 2
  [../]
[]

[Materials]
  [./heat1]
    type = HeatConductionMaterial
    block = '1 2'
    specific_heat = 1.0
    thermal_conductivity = 100000000.0
  [../]
  [./density]
    type = Density
    block = '1 2'
    density = 1.0
  [../]
[]

[Executioner]
  type = Transient
#  petsc_options = '-snes_mf_operator -ksp_monitor -snes_ksp_ew'

  #Preconditioned JFNK (default)
  solve_type = 'PJFNK'




#  petsc_options_iname = '-snes_type -snes_ls -snes_linesearch_type -ksp_gmres_restart -pc_type -pc_hypre_type -pc_hypre_boomeramg_max_iter'
#  petsc_options_value = 'ls         basic    basic                    201                hypre    boomeramg      4'
#  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type -pc_hypre_boomeramg_max_iter'
#  petsc_options_value = '201                hypre    boomeramg      4'

  nl_abs_tol = 5e-2
  nl_rel_tol = 1e-8

  l_tol = 1e-6
  l_max_its = 100

  start_time = 0.0
  dt = 1e-1
  end_time = 2.0
[]

[Postprocessors]

  [./temp_left]
    type = SideAverageValue
    boundary = 2
    variable = temp
  [../]

  [./temp_right]
    type = SideAverageValue
    boundary = 3
    variable = temp
  [../]

  [./flux_left]
    type = SideFluxIntegral
    variable = temp
    boundary = 2
    diffusivity = thermal_conductivity
  [../]

  [./flux_right]
    type = SideFluxIntegral
    variable = temp
    boundary = 3
    diffusivity = thermal_conductivity
  [../]


[Outputs]
  exodus = true
  output_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear'
  [../]
[]
