CDF      
       
len_string     !   len_line   Q   four      	time_step          len_name   !   num_dim       	num_nodes      #   num_elem      
num_el_blk        num_node_sets         num_side_sets         num_el_in_blk1        num_nod_per_el1       num_el_in_blk2        num_nod_per_el2       num_el_in_blk3        num_nod_per_el3       num_side_ss1      num_side_ss2      num_side_ss3      num_side_ss4      num_side_ss5      num_side_ss6      num_nod_ns1       num_nod_ns2       num_nod_ns3       num_nod_ns4       num_nod_ns5       num_nod_ns6       num_nod_var       num_glo_var       num_info  �         api_version       @�
=   version       @�
=   floating_point_word_size            	file_size               int64_status             title         conforming_two_var_out.e       maximum_name_length                 ,   
time_whole                            ��   	eb_status                             @   eb_prop1               name      ID              L   	ns_status         	                    X   ns_prop1      	         name      ID              p   	ss_status         
                    �   ss_prop1      
         name      ID              �   coordx                           �   coordy                           �   eb_names                       d      �   ns_names      	                 �      L   ss_names      
                 �         
coor_names                         D      �   node_num_map                    �          connect1                  	elem_type         QUAD4         �      �   connect2                  	elem_type         QUAD4         �      ,   connect3                  	elem_type         EDGE2                �   elem_num_map                    P      �   elem_ss1                             side_ss1                          ,   elem_ss2                          <   side_ss2                          L   elem_ss3                          \   side_ss3                          l   elem_ss4                          |   side_ss4                          �   elem_ss5                          �   side_ss5                          �   elem_ss6                          �   side_ss6                          �   node_ns1                          �   node_ns2                          �   node_ns3                             node_ns4                             node_ns5                          0   node_ns6                          H   vals_nod_var1                               �    vals_nod_var2                               �   vals_nod_var3                               �0   vals_nod_var4                               �H   name_nod_var                       �      \   name_glo_var                       D      �   vals_glo_var                             �`   info_records                      y�      $                 �                     e         d                           e               d?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�                              ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�                                      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�                      ?�              ?�      ?�      ?�                      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�      ?�                                                                        middle                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           	   
                                                                      !   "   #                                          	         
         	                                                                                                                                                  !   !   "   "   #                           	   
                                                                                                                                 	                        
                        	      
               
                                                                        lm_u                             lm_v                             u                                v                                l2_error                         l2_v                               ####################                                                             # Created by MOOSE #                                                             ####################                                                             ### Command Line Arguments ###                                                   -i                                                                               conforming_two_var.i                                                                                                                                              ### Version Info ###                                                             Framework Information:                                                           MOOSE version:           git commit 6501825 on 2016-03-02                        PETSc Version:           3.5.4                                                   Current Time:            Wed Mar  2 17:51:04 2016                                Executable Timestamp:    Wed Mar  2 17:36:54 2016                                       ?�y�E�3                                                                                                                                                   ### Input File ###                                                                                                                                                []                                                                                 initial_from_file_timestep     = LATEST                                          initial_from_file_var          = INVALID                                         block                          = INVALID                                         coord_type                     = XYZ                                             fe_cache                       = 0                                               kernel_coverage_check          = 1                                               material_coverage_check        = 1                                               name                           = 'MOOSE Problem'                                 restart_file_base              = INVALID                                         rz_coord_axis                  = Y                                               type                           = FEProblem                                       use_legacy_uo_aux_computation  = INVALID                                         use_legacy_uo_initialization   = INVALID                                         element_order                  = AUTO                                            order                          = AUTO                                            side_order                     = AUTO                                            active_bcs                     = INVALID                                         active_kernels                 = INVALID                                         inactive_bcs                   = INVALID                                         inactive_kernels               = INVALID                                         start                          = 0                                               control_tags                   = INVALID                                         dimNearNullSpace               = 0                                               dimNullSpace                   = 0                                               enable                         = 1                                               error_on_jacobian_nonzero_reallocation = 0                                       petsc_inames                   =                                                 petsc_options                  = INVALID                                         petsc_values                   =                                                 solve                          = 1                                               use_nonlinear                  = 1                                             []                                                                                                                                                                [BCs]                                                                                                                                                               [./all]                                                                            boundary                     = '1 2 3 4'                                         control_tags                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 type                         = FunctionDirichletBC                               use_displaced_mesh           = 0                                                 variable                     = u                                                 diag_save_in                 = INVALID                                           function                     = exact_sln                                         save_in                      = INVALID                                           seed                         = 0                                               [../]                                                                                                                                                             [./allv]                                                                           boundary                     = '1 2 3 4'                                         control_tags                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 type                         = DirichletBC                                       use_displaced_mesh           = 0                                                 variable                     = v                                                 diag_save_in                 = INVALID                                           save_in                      = INVALID                                           seed                         = 0                                                 value                        = 0                                               [../]                                                                          []                                                                                                                                                                [Constraints]                                                                                                                                                       [./ced_u]                                                                          type                         = EqualValueConstraint                              control_tags                 = Constraints                                       enable                       = 1                                                 execute_on                   = LINEAR                                            interface                    = middle                                            master_variable              = u                                                 slave_variable               = INVALID                                           use_displaced_mesh           = 0                                                 variable                     = lm_u                                            [../]                                                                                                                                                             [./ced_v]                                                                          type                         = EqualValueConstraint                              control_tags                 = Constraints                                       enable                       = 1                                                 execute_on                   = LINEAR                                            interface                    = middle                                            master_variable              = v                                                 slave_variable               = INVALID                                           use_displaced_mesh           = 0                                                 variable                     = lm_v                                            [../]                                                                          []                                                                                                                                                                [Executioner]                                                                      type                           = Steady                                          compute_initial_residual_before_preset_bcs = 0                                   control_tags                   =                                                 enable                         = 1                                               l_abs_step_tol                 = -1                                              l_max_its                      = 10000                                           l_tol                          = 1e-12                                           line_search                    = default                                         nl_abs_step_tol                = 1e-50                                           nl_abs_tol                     = 1e-50                                           nl_max_funcs                   = 10000                                           nl_max_its                     = 50                                              nl_rel_step_tol                = 1e-50                                           nl_rel_tol                     = 1e-12                                           no_fe_reinit                   = 0                                               petsc_options                  = INVALID                                         petsc_options_iname            = INVALID                                         petsc_options_value            = INVALID                                         restart_file_base              =                                                 solve_type                     = INVALID                                         splitting                      = INVALID                                       []                                                                                                                                                                [Executioner]                                                                      _fe_problem                    = 0x7fe1c885de00                                []                                                                                                                                                                [Functions]                                                                                                                                                         [./exact_sln]                                                                      type                         = ParsedFunction                                    control_tags                 = Functions                                         enable                       = 1                                                 vals                         = INVALID                                           value                        = y                                                 vars                         = INVALID                                         [../]                                                                                                                                                             [./ffn]                                                                            type                         = ParsedFunction                                    control_tags                 = Functions                                         enable                       = 1                                                 vals                         = INVALID                                           value                        = 0                                                 vars                         = INVALID                                         [../]                                                                          []                                                                                                                                                                [Kernels]                                                                                                                                                           [./coupled_u]                                                                      type                         = CoupledForce                                      block                        = INVALID                                           control_tags                 = Kernels                                           diag_save_in                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 v                            = u                                                 variable                     = v                                               [../]                                                                                                                                                             [./diff_u]                                                                         type                         = Diffusion                                         block                        = INVALID                                           control_tags                 = Kernels                                           diag_save_in                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = u                                               [../]                                                                                                                                                             [./diff_v]                                                                         type                         = Diffusion                                         block                        = INVALID                                           control_tags                 = Kernels                                           diag_save_in                 = INVALID                                           enable                       = 1                                                 implicit                     = 1                                                 save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = v                                               [../]                                                                                                                                                             [./ffn]                                                                            type                         = UserForcingFunction                               block                        = INVALID                                           control_tags                 = Kernels                                           diag_save_in                 = INVALID                                           enable                       = 1                                                 function                     = ffn                                               implicit                     = 1                                                 save_in                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = u                                               [../]                                                                          []                                                                                                                                                                [Mesh]                                                                             displacements                  = INVALID                                         block_id                       = INVALID                                         block_name                     = INVALID                                         boundary_id                    = INVALID                                         boundary_name                  = INVALID                                         construct_side_list_from_node_list = 0                                           ghosted_boundaries             = INVALID                                         ghosted_boundaries_inflation   = INVALID                                         patch_size                     = 40                                              second_order                   = 0                                               skip_partitioning              = 0                                               type                           = FileMesh                                        uniform_refine                 = 0                                               centroid_partitioner_direction = INVALID                                         control_tags                   =                                                 dim                            = 3                                               distribution                   = DEFAULT                                         enable                         = 1                                               file                           = 2blk-conf.e                                     nemesis                        = 0                                               partitioner                    = default                                         patch_update_strategy          = never                                                                                                                            [./MortarInterfaces]                                                                                                                                                [./middle]                                                                         master                     = 100                                                 slave                      = 101                                                 subdomain                  = 1000                                              [../]                                                                          [../]                                                                          []                                                                                                                                                                [Mesh]                                                                                                                                                              [./MortarInterfaces]                                                                                                                                                [./middle]                                                                       [../]                                                                          [../]                                                                          []                                                                                                                                                                [Outputs]                                                                          append_date                    = 0                                               append_date_format             = INVALID                                         checkpoint                     = 0                                               color                          = 1                                               console                        = 1                                               controls                       = 0                                               csv                            = 0                                               dofmap                         = 0                                               execute_on                     = 'INITIAL TIMESTEP_END'                          exodus                         = 1                                               file_base                      = INVALID                                         gmv                            = 0                                               gnuplot                        = 0                                               hide                           = INVALID                                         interval                       = 1                                               nemesis                        = 0                                               output_if_base_contains        = INVALID                                         print_linear_residuals         = 1                                               print_mesh_changed_info        = 0                                               print_perf_log                 = 0                                               show                           = INVALID                                         solution_history               = 0                                               sync_times                     =                                                 tecplot                        = 0                                               vtk                            = 0                                               xda                            = 0                                               xdr                            = 0                                             []                                                                                                                                                                [Postprocessors]                                                                                                                                                    [./l2_error]                                                                       type                         = ElementL2Error                                    block                        = '1 2'                                             control_tags                 = Postprocessors                                    enable                       = 1                                                 execute_on                   = 'INITIAL TIMESTEP_END'                            function                     = exact_sln                                         outputs                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = u                                               [../]                                                                                                                                                             [./l2_v]                                                                           type                         = ElementL2Norm                                     block                        = '1 2'                                             control_tags                 = Postprocessors                                    enable                       = 1                                                 execute_on                   = 'INITIAL TIMESTEP_END'                            outputs                      = INVALID                                           seed                         = 0                                                 use_displaced_mesh           = 0                                                 variable                     = v                                               [../]                                                                          []                                                                                                                                                                [Preconditioning]                                                                                                                                                   [./fmp]                                                                            line_search                  = default                                           petsc_options                = INVALID                                           petsc_options_iname          = INVALID                                           petsc_options_value          = INVALID                                           solve_type                   = NEWTON                                            type                         = SMP                                               control_tags                 = Preconditioning                                   coupled_groups               = INVALID                                           enable                       = 1                                                 full                         = 1                                                 off_diag_column              = INVALID                                           off_diag_row                 = INVALID                                           pc_side                      = right                                           [../]                                                                          []                                                                                                                                                                [Variables]                                                                                                                                                         [./lm_u]                                                                           block                        = middle                                            eigen                        = 0                                                 family                       = LAGRANGE                                          initial_condition            = INVALID                                           order                        = FIRST                                             outputs                      = INVALID                                           scaling                      = 1                                                 initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                                                                                                             [./lm_v]                                                                           block                        = middle                                            eigen                        = 0                                                 family                       = LAGRANGE                                          initial_condition            = INVALID                                           order                        = FIRST                                             outputs                      = INVALID                                           scaling                      = 1                                                 initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                                                                                                             [./u]                                                                              block                        = '1 2'                                             eigen                        = 0                                                 family                       = LAGRANGE                                          initial_condition            = INVALID                                           order                        = FIRST                                             outputs                      = INVALID                                           scaling                      = 1                                                 initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                                                                                                             [./v]                                                                              block                        = '1 2'                                             eigen                        = 0                                                 family                       = LAGRANGE                                          initial_condition            = INVALID                                           order                        = FIRST                                             outputs                      = INVALID                                           scaling                      = 1                                                 initial_from_file_timestep   = LATEST                                            initial_from_file_var        = INVALID                                         [../]                                                                          []                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          ?�y�E�3        ?�                                                                                                                                                                                                                                                      @�Ez��?�E}!|�?�� � �@������ei                                                                                                                                                                                                                                                ?�DS�#?z2�b��?�ZS�,س?�.��)%P�֘& ��?������d?������??�������?�������                ?������@        ?�������?�������?�������                ?�������?�������?�������?�     ?�     �?�������?�������?�     �?�������?�     ?�������?�������?�������?�������?�������?�������?�������                                        ?��+�Һ?�~:�ky?���	3�?��m���f                ?���	3��        ?��m��(�                                                        ?�L��]7z?��H�+{�        ?��+��?��m�ۨ�?��H�+v�?��m���+                                                                                                <�8B1�?�8F �O|