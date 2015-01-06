[Mesh]
  type = GeneratedMesh
  dim = 2

  nx = 10
  ny = 100

  xmin = 0.0
  xmax = 1.0

  ymin = 0.0
  ymax = 10.0

  # The centroid partitioner orders elements based on
  # the position of their centroids
  partitioner = centroid

  # This will order the elements based on the y value of
  # their centroid.  Perfect for meshes predominantly in
  # one direction
  centroid_partitioner_direction = y

  # The centroid partitioner behaves differently depending on
  # whether you are using Serial or ParallelMesh, so to get
  # repeatable results, we restrict this test to using SerialMesh.
  distribution = serial
[]

[Variables]
  active = 'u'

  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./proc_id]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  active = 'diff'

  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[AuxKernels]
  [./proc_id]
    type = ProcessorIDAux
    variable = proc_id
  [../]
[]

[BCs]
  active = 'left right'

  [./left]
    type = DirichletBC
    variable = u
    boundary = 3
    value = 0
  [../]

  [./right]
    type = DirichletBC
    variable = u
    boundary = 1
    value = 1
  [../]
[]

[Executioner]
  type = Steady

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'
[]

[Outputs]
  file_base = out
  output_on = 'initial timestep_end'
  [./exodus]
    type = Exodus
    elemental_as_nodal = true
  [../]
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear linear'
  [../]
[]
