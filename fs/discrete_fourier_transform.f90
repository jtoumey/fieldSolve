function discrete_fourier_transform() return(0)


end function discrete_fourier_transform


program ft_driver
    implicit none

    integer, parameter :: n = 10
    integer :: ii
    real, parameter :: pi = 3.14159265357989
    real, parameter :: period = 2*pi
    real, dimension(n) :: sig_real, sig_imag


    ! Initialize the signal
    do ii = 1, n
        sig_real(ii) = sin(ii*1.0)
        sig_imag(ii) = 0.0
    end do


end program ft_driver
