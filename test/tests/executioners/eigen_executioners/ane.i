[Mesh]
 type = GeneratedMesh
 dim = 2
 xmin = 0
 xmax = 10
 ymin = 0
 ymax = 10
 elem_type = QUAD4
 nx = 8
 ny = 8

 uniform_refine = 0
[]

# the minimum eigenvalue is (2*PI*(p-1)^(1/p)/a/p/sin(PI/p))^p;
# Its inverse is 35.349726539758187. Here a is equal to 10.

[Variables]
  active = 'u'

  [./u]
    # second order is way better than first order
    order = FIRST
    family = LAGRANGE
  [../]
[]

[ICs]
  [./uic]
    type = RandomIC
    variable = u
  [../]
[]

[Kernels]
  active = 'diff rhs'

  [./diff]
    type = PHarmonic
    variable = u
    p = 3
  [../]

  [./rhs]
    type = PMassEigenKernel
    variable = u
    p = 3
  [../]
[]

[BCs]
  active = 'homogeneous'

  [./homogeneous]
    type = DirichletBC
    variable = u
    boundary = '0 2'
    value = 0
  [../]
[]

[Executioner]
  type = NonlinearEigen

  bx_norm = 'unorm'
  xdiff = 'udiff'

  free_power_iterations = 10
  source_abs_tol = 1e-12
  source_rel_tol = 1e-50
  k0 = 1.0
# important: constant initial value set by auto_initilization does not
# converge to the fundamental mode
  auto_initialization = false
  output_on_final = true

  #Preconditioned JFNK (default)
  solve_type = 'PJFNK'
  l_max_its = 100
[]

[Postprocessors]
  active = 'unorm udiff'

  [./unorm]
    type = ElementIntegralVariablePostprocessor
    variable = u
    # execute on residual is important for nonlinear eigen solver!
    execute_on = linear
  [../]

  [./udiff]
    type = ElementL2Diff
    variable = u
    outputs = console
  [../]
[]

[Outputs]
  file_base = ane
  interval = 1
  exodus = true
  [./console]
    type = Console
    perf_log = true
    output_on = 'failed nonlinear linear timestep_end'
  [../]
[]
