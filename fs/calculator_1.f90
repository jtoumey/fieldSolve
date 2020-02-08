

program runge_kutta

implicit none

real :: t0, t1, tn, dt
integer :: ii, jj, kk
integer, parameter :: num_steps = 8

t0 = 1.0
t1 = 2.0

dt = (t1 - t0)/num_steps


do ii = 0, num_steps - 1
    tn = t0 + (ii + 1)*dt
    print *, tn
end do

real :: x = 0.5
character(len=*), parameter :: fmt = "(a, f0.1, a, f0.5)"

x = 0.1 + this_image()/10.0
select case (this_image())
    case (1)
        print fmt, "sine(", x, ") = ", sin(x)
    case (2)
        print fmt, "cosine(", x, ") = ", cos(x)
    case (3)
        print fmt, "tangent(", x, ") = ", tan(x)
end select

end program runge_kutta
