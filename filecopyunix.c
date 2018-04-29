
    #include <stdio.h>
    #include <stdlib.h>

    int main()
    {
        int c ; 
        c = getchar();
        while( c != EOF )
        {

           if ( c != 12 ) 
              putchar( c );

           c = getchar();
        }
	return 0;
    }



