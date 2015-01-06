[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
  nx = 2
  ny = 2
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./v]
  [../]
[]

[AuxKernels]
  [./one]
    type = ConstantAux
    variable = v
    value = 1
  [../]
[]

[Postprocessors]
  # This postprocessor is listed first on purpose to give the resolver something to do
  [./diff]
    type = DifferencePostprocessor
    value1 = nodes
    value2 = elems
  [../]
  [./nodes]
    type = NumNodes
  [../]
  [./elems]
    type = NumElems
  [../]
[]

[Problem]
  type = FEProblem
  solve = false
  kernel_coverage_check = false
[]

[Executioner]
  type = Steady
[]

[Outputs]
  csv = true
  output_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear linear'
  [../]
[]
