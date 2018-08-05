! A fortran95 program for G95
! By WQY
!  proj1.f90
!
!  FUNCTIONS:
!  proj1 - Entry point of console application.
!

!****************************************************************************
!
!  PROGRAM: proj1
!
!  PURPOSE:  Entry point for the console application.
!
!****************************************************************************

    program proj1

    implicit none

    ! Variables

    !integer :: MAX_N = 10
    real, dimension (10, 10) :: G_matr, U_matr, S_matr!S- собств вектора
    real, dimension (10) :: Psi_vec
    real :: e_const = 4.935
    real :: pi = 3.1416
    real :: alpha = 1
    real :: beta = 1
    real :: EPS = 10**(-4)
    real :: TAUSQ = 0
    !real :: delta_x = 0.1
    integer :: i , j, k, x
    integer :: N = 10
    integer :: IR = 0
    integer :: IN = 100

    ! Assigning  values

    ! Body of proj1
    do i=1,10
      do j = 1, 10
          if (i == j) then
            G_matr (i, j) = e_const*i*i;
          else
            G_matr (i, j) = 0;
          end if
      end do
   end do

 do i=1,10
      do j = 1, 10
          if (i == j) then
            U_matr (i, j) = alpha*((-1)**(i+j+1) + 1)/((pi*(i+j))**2)
          else
            U_matr (i, j) = alpha*((-1)**(i+j) - 1)/((pi*(i-j))**2) -&
                            alpha*((-1)**(i+j) - 1)/((pi*(i+j))**2)
          end if
      end do
   end do


  do i=1,10
      do j = 1, 10
          G_matr (i, j) = G_matr (i, j) + U_matr(i,j)
      end do
   end do


   !SUBROUTINE VOEVDN(G_matr, S_matr, N, IN, EPS, IR, TAUSQ)
   !REAL G_matr(10, 10), S_matr(10, 10), EPS, TAUSQ
   !INTEGER N, IN, IR

    CALL VOEVDN(G_matr, S_matr, N, IN, EPS, IR, TAUSQ)

    print*, TAUSQ

    ! использую delta_x = 0.1
    open(1, file= "res.txt")


    do x=1,9
        print *, "x = ", x*1.0/10
        do i = 1, 10
            do k = 1, 10
                if (k == 1) then
                    Psi_vec(i) = S_matr(k,i)*( SQRT(2.0)*SIN(pi*k*x/10) )
                else
                    Psi_vec(i) = Psi_vec(i) + S_matr(k,i)*( SQRT(2.0)*SIN(pi*k*x/10) )
                end if
            end do
        end do
        print *, Psi_vec
        !write(1,*) (j=1,10,Psi_vec(j))
     end do

    close(1)
    end program proj1

