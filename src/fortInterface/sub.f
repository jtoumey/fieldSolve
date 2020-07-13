      SUBROUTINE SUB(FSIZE, FVEC, SUM)

      INTEGER FSIZE, I
      REAL*8 FVEC(FSIZE)
      REAL*8 SUM
C.....
      SUM = 0.0

      DO I = 1, FSIZE
          SUM = SUM + FVEC(I)
      END DO

      END