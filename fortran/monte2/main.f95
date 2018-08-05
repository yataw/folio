! A fortran95 program for G95
! By WQY

subroutine init_random_seed()
  integer :: i, n, clock
  integer, dimension(:), allocatable :: seed

  call random_seed(size = n)
  allocate(seed(n))

  call system_clock(count=clock)

  seed = clock + 37 * (/ (i - 1, i = 1, n) /)
  call random_seed(put = seed)

  deallocate(seed)
end subroutine init_random_seed


program main
  real :: x1 = -3.1415, x2 = 3.1415,&
          y1 = -3, y2 = 3,&
          a = 1.5, f1x = -1, f1y = 0.1, f2x = 1, f2y = 0.1,&
          r = 0, total = 0, argx, argy, s
  integer :: N = 1000000, N_ok = 0, i = 1


  call init_random_seed()

  do i = 1, N
    call RANDOM_NUMBER (r)
    argx = x1 + (x2 - x1)*r
    call RANDOM_NUMBER (r)
    argy = y1 + (y2 - y1)*r

    s = sqrt((argx - f1x)**2 + (argy - f1y)**2) +&
         sqrt((argx - f2x)**2 + (argy - f2y)**2)
    if (s > 2*a) then
        N_ok = N_ok + 1
        total = total + ABS(SIN(argx*argy))
    end if
  end do

   total = total/N_ok
   print*, "Result = ", total*(x2 - x1)*(y2 - y1)

end
