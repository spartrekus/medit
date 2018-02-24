
////////////////////////////////////////////////////////////////////////////////////////
// medit for Easy First Basic C Steps for All Beginners and Young Programmers !!!
// Year of Back to Future: 2012
////////////////////////////////////////////////////////////////////////////////////////
// To compile: tcc or gcc or cc;   cc -lncurses -lm editor.c -o editor 
////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#if defined(__linux__)
#define MYOS 1
#define PATH_MAX 2500
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__)
#define MYOS 4
#define PATH_MAX 2500
#else
#define MYOS 0
#endif

float editor_version = 0.21;

#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>

int rows, cols;
int rowmax; 
int toxin=0;
int color_scheme=2;

#define SHIFTY 2
#define SHIFTX 1



// fexist
//#include <stdlib.h>
//#include <string.h>
#include <dirent.h> 
#include <ctype.h>
#include <sys/stat.h> //st
#include <sys/types.h>
#include <unistd.h>  
//#include <time.h>



////////////////////////////////
////////////////////////////////
////////////////////////////////
void mvcenter( int myposypass, char *mytext )
{
      mvprintw( myposypass, cols/2 - strlen( mytext )/2  , "%s", mytext );
}

void gfxhline( int y1, int x1, int x2 , int thechar )
{
    int foo, fooy , foox ;
    foo = x1;
    for( foox = x1 ; foox <= x2 ; foox++) 
      mvaddch( y1 , foox , thechar );
}


void gfxrectangle( int y1, int x1, int y2, int x2 )
{
    int foo, fooy , foox ;
    foo = x1;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
     for( foox = x1 ; foox <= x2 ; foox++) 
      mvaddch( fooy , foox , ' ' );
}



void gfxframe( int y1, int x1, int y2, int x2 )
{
    int foo, fooy , foox ;
    foo = x1;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
        mvaddch( fooy , foo , ACS_VLINE );
    foo = x2;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
         mvaddch( fooy , foo , ACS_VLINE );
    foo = y1;
    for( foox = x1 ; foox <= x2 ; foox++) 
         mvaddch( foo , foox , ACS_HLINE );
    foo = y2;
    for( foox = x1 ; foox <= x2 ; foox++) 
         mvaddch( foo , foox , ACS_HLINE );
    mvaddch( y1 , x1 , ACS_ULCORNER );
    mvaddch( y1 , x2 , ACS_URCORNER );
    mvaddch( y2 , x1 , ACS_LLCORNER );
    mvaddch( y2 , x2 , ACS_LRCORNER );
}




////////////////////////////////
void ncurses_runcmd( char *thecmd   )
{
       char rncmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( rncmdi , "  " , PATH_MAX );
       strncat( rncmdi , thecmd , PATH_MAX - strlen( rncmdi ) -1 );
       strncat( rncmdi , " " , PATH_MAX - strlen( rncmdi ) -1 );
       system( rncmdi );
       reset_prog_mode();
}






int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}










//////////////////////////////
//////////////////////////////
//////////////////////////////
char *fbasenoext(char* mystr)
{
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}







//////////////////////////////
//////////////////////////////
//////////////////////////////
void make_c( char *thefile )
{
       char targetfile[PATH_MAX];
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();

       strncpy( targetfile, fbasenoext( thefile ) , PATH_MAX );
       strncat( targetfile , ".bin" , PATH_MAX - strlen( targetfile ) -1 );

       strncpy( cmdi , " gcc -lncurses -lm  " , PATH_MAX );
       strncat( cmdi , "  \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thefile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"  " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " -o \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , targetfile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"  " , PATH_MAX - strlen( cmdi ) -1 );
       printf( "=> TURBO CMD: %s\n", cmdi );
       system( cmdi );

       strncpy( cmdi , "  " , PATH_MAX );
       strncat( cmdi , "  ./\"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , targetfile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"  " , PATH_MAX - strlen( cmdi ) -1 );
       printf( "=> TURBO CMD: %s\n", cmdi );
       system( cmdi );

       printf( "<Press Enter> " ); 
       int ccd = 0; ccd = getchar();
       //scanf( "<>" , &ccd );

       reset_prog_mode();
}












void editor_menu_beon() 
{
        int editor_menu_gameover = 0;
        int ch = 0; int fooquestion ; int i;  int kittux;
        while( editor_menu_gameover == 0)
        {
               attroff( A_BOLD ); attroff( A_REVERSE ); curs_set( 1 );
               color_set( 13, NULL ); attroff( A_REVERSE );
               gfxrectangle( rows*25/100, cols*25/100 , rows*75/100, cols*75/100 );
               gfxframe( rows*25/100, cols*25/100 , rows*75/100, cols*75/100 );
               color_set( 17, NULL ); attron( A_REVERSE );
               mvcenter( rows*25/100, "| Menu BeON |" );
               color_set( 13, NULL ); attroff( A_REVERSE ); 
               kittux = 2;
               mvprintw( rows*25/100 +kittux++, cols*25/100+2, "?: HELP! " );
               mvprintw( rows*25/100 +kittux++, cols*25/100+2, "h: HELP! " );
               mvprintw( rows*25/100 +kittux++, cols*25/100+2, "e: Web Internet Browser " );
               mvprintw( rows*25/100 +kittux++, cols*25/100+2, "f: Firefox Web Internet Browser " );
               mvprintw( rows*25/100 +kittux++, cols*25/100+2, "p: Pascal Programming " );
               mvprintw( rows*25/100 +kittux++, cols*25/100+2, "s: Game nsnake " );
               mvprintw( rows*25/100 +kittux++, cols*25/100+2, "o: Game ninvaders " );
               mvprintw( rows*25/100 +kittux++, cols*25/100+2, "n: naclock " );
               mvprintw( rows*25/100 +kittux++, cols*25/100+2, "i: Cancel" );
               color_set( 5, NULL ); attron( A_REVERSE );
               mvcenter( rows*75/100 -1, "[ Esc: Cancel ]" );

               ch = getch();

               if ( ch == 'i' ) editor_menu_gameover = 1;
               else if ( ch == 27 ) editor_menu_gameover = 1;
               else if ( ch == KEY_F(9) ) editor_menu_gameover = 1;
               else if ( ch == 'o' ) ncurses_runcmd( " ninvaders " );
               else if ( ch == 's' ) ncurses_runcmd( " nsnake " );
               else if ( ch == 'n' ) ncurses_runcmd( " naclock " );
               else if ( ch == 'e' ) ncurses_runcmd( " links google.com " );
               else if ( ch == 'f' ) ncurses_runcmd( " iceweasel google.com " );
               else if ( ch == 'p' ) ncurses_runcmd( " fp " );

         }
}








//////////////
#define TABSIZE 8
#define CHUNKSIZE 1024
#define STRMAX 64
#define BUFSIZE 256

#ifdef CTRL
#undef CTRL
#endif
#define CTRL(a) ((a) & 31)

char	*text = 0;
int	text_size = 0;

char	file_name[STRMAX] = "", block_name[STRMAX] = "";
char	find_str[STRMAX] = "", replace_str[STRMAX] = "";

int	bos_pos = 0, eos_pos = 0, cur_pos = 0, eof_pos = 0, bow_line = 0;
int	bow_line_prev = 0, win_shift = 0, cur_line = 0, cur_y = 0, cur_x = 0;
int	is_changed = 0, ins_mode = 1, find_mode = 0;

#define	ALIGN(x,mod)	(((x) / (mod) + 1) * (mod))
#define nexttab(x)	ALIGN (x, TABSIZE)
#define align_chunk(x)	ALIGN (x, CHUNKSIZE)



void	adduch (unsigned char ch)
{
	if ((ch >= 32 && ch < 128) || ch >= 160)	/* ^C or ~C */
		addch (ch);
	else {
		attron (A_BLINK);
		addch (ch > 128 && ch < 159 ? ch - 32 : ch + 64);
		attroff (A_BLINK);
	}
}





int confirm(char *s)
{
	int	ch;
	move(rowmax-1, 0);
	attron (A_BOLD);
	addstr (s);
	attroff (A_BOLD);
	clrtoeol ();
	refresh ();
	ch = getch ();
	return ch == 'y' || ch == 'Y';
}






int enter_string (char *s, char *buf)
{
	int b_len, ch, flag = 1;

	for (;;) 
        {
		//move (rowmax - 1, 0);
		move(rows-1, 0);
		//attron (A_BOLD);
		addstr(s);
		//attroff (A_BOLD);
		for (b_len = 0; buf[b_len]; b_len++)
			adduch (buf[b_len]);
		clrtoeol();
		refresh ();
		ch = getch ();
		switch (ch) {

		case CTRL ('Y'):
			*buf = 0;
			break;

		case CTRL ('Q'):
			ch = getch ();
			goto ins_char;
                        //gameover = 1;
                        //break;

		case KEY_BACKSPACE:
			if (b_len)
				buf[b_len - 1] = 0;
			break;
		case '\r':
			return 1;
		case CTRL ('X'):
			return 0;
		default:
			if (!iscntrl (ch)) {
		ins_char:	if (flag)
					*buf = b_len = 0;
				if (b_len < STRMAX - 1) {
					buf[b_len] = ch;
					buf[b_len + 1] = 0;
				}
			} else
				beep ();
			break;
		}
		flag = 0;
	}
	/* NOTREACHED */
}

int	error (char *s, ...)
{
	va_list	args;
	char	buf[BUFSIZE];
	int	i = 0;

	va_start (args, s);
	i += snprintf (buf + i, BUFSIZE - i, "Error ");
	if (*s != '$')
		i += vsnprintf (buf + i, BUFSIZE - i, s, args);
	else {
		i += vsnprintf (buf + i, BUFSIZE - i, s + 1, args);
		i += snprintf (buf + i, BUFSIZE - i, ", %s", strerror (errno));
	}
	va_end (args);
	beep ();
	confirm (buf);

	return 0;	/* convinient */
}

int	bol (int pos)
{
	while (pos && text[pos - 1] != '\n')
		pos--;
	return pos;
}

int	prevline (int pos)
{
	pos = bol (pos);
	return pos ? bol (pos - 1) : 0;
}

int	eol (int pos)
{
	while (pos < eof_pos && text[pos] != '\n')
		pos++;
	return pos;
}

int	nextline (int pos)
{
	pos = eol (pos);
	return pos < eof_pos ? pos + 1 : pos;
}

int	win_x (int line, int xx)
{
	int	i, x = 0;

	for (i = line; i < eof_pos && i < line + xx; i++)
		if (text[i] == '\n')
			break;
		else if (text[i] == '\t')
			x = nexttab (x);
		else
			x++;
	return x;
}

int	pos_x (int line, int xx)
{
	int	i, x = 0;

	for (i = line; i < eof_pos && x < xx; i++)
		if (text[i] == '\n')
			break;
		else if (text[i] == '\t')
			x = nexttab (x);
		else
			x++;
	return i;
}










void color_c1() //black
{
    color_set( 0, NULL ); attroff( A_BOLD ); attroff( A_REVERSE );
}
void color_c2() //status
{
    color_set( 6, NULL ); attroff( A_BOLD ); attron( A_REVERSE ); 
}

void color_c5() //deep blue, the grand bleu
{
    color_set( 11, NULL ); attroff( A_BOLD ); attroff( A_REVERSE );
}

void color_c6() //commands color
{
    color_set( 12, NULL ); 
    attroff( A_REVERSE );
    attron( A_BOLD );
}

void color_c7() //include color
{
    color_set( 19, NULL ); 
    attroff( A_REVERSE );
    attron( A_BOLD );
}










void clearscreen(void)
{
    attroff( A_BOLD ); attroff( A_REVERSE );
    if ( color_scheme == 1 )
    {
      color_c5();
      erase();
      gfxrectangle( 0, 0, rows-1, cols-1 ); // low end 
      gfxframe( 1, 0, rows-2, cols-1 );     // low end 
    }
    else if ( color_scheme == 2 )
    {
      color_c1();
      erase();
    }
}



void showstatus(void)
{
    int foxy;
    color_c2(); 
    gfxhline( 0,      0, cols-1 , ' ' );
    mvprintw( 0, 0, "|MEDIT v%0.1f|by Spartrekus (GNU)|  [FILE:%s]", editor_version , file_name );

    color_c2(); 
    for( foxy=0; foxy++; foxy <= cols-3 ) mvprintw( rows-1, foxy , " " );

    color_c1(); mvprintw( rows-1, 0, " F1" );
    color_c2(); printw( "Help " );
    color_c1(); printw( " F2" );  color_c2(); printw( "Save " );
    color_c1(); printw( " F5" );  color_c2(); printw( "Make " );
    color_c1(); printw( " F6" );  color_c2(); printw( "Mode " );
    color_c1(); printw( " F9" );  color_c2();  printw( "Menu " );
    color_c1(); printw( " F10" ); color_c2(); printw( "Quit! " );
}



////////////////////////
void show(void)
{
	int	i, m, t, j;
	/*
	 * speed up scrolling
	 */
	if (bow_line > bow_line_prev) {
		m = bow_line_prev;
		for (i = 0; m != bow_line && i < rowmax; i++)
			m = nextline (m);
		if (i < rowmax)
			scrl (i);
	} else if (bow_line < bow_line_prev) {
		m = bow_line_prev;
		for (i = 0; m != bow_line && i < rowmax; i++)
			m = prevline (m);
		if (i < rowmax)
			scrl (-i);
	}
	bow_line_prev = bow_line;


	//erase();
        int newline = 0 ; 
        int fontcolor1 = 0; //null

	if (!text)
		return;

	for (m = bow_line, i = 0; m < eof_pos && i < rowmax; i++) 
        {
                //mvprintw( rows-2, 0, "|%d|L:%d| %c", toxin, newline, text[ 0 ] );
		m = pos_x(m, win_shift);
		move(i+SHIFTY, 0+SHIFTX );
#define EOS_COLS (i < rowmax - 1 ? COLS : COLS - 1)

		for (j = 0; m < eof_pos && j < EOS_COLS; m++) {

			if (m >= bos_pos && m < eos_pos)
				attron (A_REVERSE);
			else
				attroff (A_REVERSE);

                        /// basic  colors for '#' and '!' at begin of new line
                        if ( text[m] == '\n')
                           newline = 1; 
                        else 
                        {
                           if ( newline == 1 ) 
                           {
                              if (text[m] == '#')      fontcolor1 = 1; 
                              else if (text[m] == '!') fontcolor1 = 2;  // commands
                              else { fontcolor1 = 0; }
                              newline = 0;
                           }
                        }

                        /// green 
                        if ( color_scheme == 2 ) if ( text[m]  == '{' ) fontcolor1 = 3;
                        if ( color_scheme == 2 ) if ( text[m]  == '}' ) fontcolor1 = 3;
                        if ( color_scheme == 2 ) 
                           if ( text[m]  == '/' ) 
                             if ( text[m+1]  == '/' ) fontcolor1 = 4;

                        /// basic yellow commands int, while, for, printf
                        if ( color_scheme == 1 )
                        if ( text[m]   == 'i' )
                        if ( text[m+1] == 'n' )
                        if ( text[m+2] == 't' )
                        if ( text[m+3] == ' ' )  
                            fontcolor1 = 2;

                        if ( color_scheme == 1 )
                        if ( text[m]   == 'w' )
                        if ( text[m+1] == 'h' )
                        if ( text[m+2] == 'i' )
                        if ( text[m+3] == 'l' )
                        if ( text[m+4] == 'e' )
                        if ( text[m+5] == ' ' )  
                            fontcolor1 = 2;

                        if ( color_scheme == 1 )
                        if ( text[m]   == 'f' )
                        if ( text[m+1] == 'o' )
                        if ( text[m+2] == 'r' )
                        if ( text[m+3] == ' ' )  
                            fontcolor1 = 2;

                        if ( color_scheme == 1 )
                        if ( text[m]   == 'r' )
                        if ( text[m+1] == 'e' )
                        if ( text[m+2] == 't' )
                        if ( text[m+3] == 'u' )  
                        if ( text[m+4] == 'r' )
                        if ( text[m+5] == 'n' )
                        if ( text[m+6] == ' ' )  
                            fontcolor1 = 2;

                        if ( color_scheme == 1 )
                        if ( text[m]   == 'p' )
                        if ( text[m+1] == 'r' )
                        if ( text[m+2] == 'i' )
                        if ( text[m+3] == 'n' )  
                        if ( text[m+4] == 't' )
                        if ( text[m+5] == 'f' )
                        if ( text[m+6] == '(' )  
                            fontcolor1 = 2;

                        if ( color_scheme == 1 )  
                        if ( text[m]   == ' ' ) fontcolor1 = 0;  // set to default color if space

                        // regular main core of programm
			if (text[m] == '\n')
		       		break;

			else if (text[m] == '\t')
				for (t = nexttab (j); j < t; j++)
					addch (' ');
			else    
                        {
                                /////[[
                                if ( color_scheme == 1 )  
                                {
                                  color_c5();
                                  if ( fontcolor1 == 1 )      color_c7(); 
                                  else if ( fontcolor1 == 2 ) color_c6(); 
                                }
                                else if ( color_scheme == 2 )  
                                {
                                   attroff( A_BOLD ); attroff( A_REVERSE );
                                   color_c1(); attroff( A_BOLD );
                                   if ( fontcolor1 == 1 )      {  color_set( 5, NULL );  attron(A_BOLD ); }
                                   else if ( fontcolor1 == 2 ) { color_set( 3, NULL );   attron(A_BOLD ); }   
                                   else if ( fontcolor1 == 3 ) { color_set( 2, NULL );   attron(A_BOLD );  fontcolor1 = 0; }   
                                   else if ( fontcolor1 == 4 ) { color_set( 4, NULL );   attron(A_BOLD ); }   
                                }
                                /////]]
				adduch( text[m] );
				j++;
			}


		}
		if (m >= bos_pos && m < eos_pos)
			while (j++ < EOS_COLS)
				addch (' ');
#undef EOS_COLS
		m = nextline (m);
	}
	attroff (A_REVERSE);
}




void	k_up (void)
{
	cur_line = prevline (cur_line);
	cur_pos = pos_x (cur_line, cur_x + win_shift);
}

void	k_down (void)
{
	if (eol (cur_pos) < eof_pos) {
		cur_line = nextline (cur_line);
		cur_pos = pos_x (cur_line, cur_x + win_shift);
	}
}

int	ins_mem (int size)
{
	char	*p;
	int	i;

	if (!text || eof_pos + size > text_size) {
		i = align_chunk (eof_pos + size);
		p = realloc (text, i);
		if (!p)
			return error ("- no memory");
		text = p;
		text_size = i;
	}
	/*
	 * read last sentence in BUGS section of memcpy(3) in FreeBSD,
	 * also bcopy(3) is not in ``ISO C''
	 */
	for (i = eof_pos - 1; i >= cur_pos; i--)
		text[i + size] = text[i];
	eof_pos += size;
	if (bos_pos >= cur_pos)
		bos_pos += size;
	if (eos_pos > cur_pos)
		eos_pos += size;
	is_changed = 1;
	return 1;
}

void	del_mem (int pos, int size)
{
	int	i;
	char	*p;

	for (i = pos + size; i < eof_pos; i++)	/* read comment to ins_mem() */
		text[i - size] = text[i];
	eof_pos -= size;
	is_changed = 1;
#define del_pos(p) (p > pos + size ? p -= size : p > pos ? p = pos : p)
	del_pos (bos_pos);
	del_pos (eos_pos);
	del_pos (cur_pos);
	del_pos (bow_line);
	del_pos (bow_line_prev);
#undef del_pos
	i = align_chunk (eof_pos);
	if (i < text_size) {
		p = realloc (text, i);
		if (!p) {
			error ("- realloc to decrease failed?");
			return;
		}
		text = p;
		text_size = i;
	}
}

void	ins_ch (char ch)
{
	if (!ins_mode && cur_pos < eof_pos) {
		if (ch == '\n') {
			cur_pos = nextline (cur_pos);
			return;
		} else if (text[cur_pos] != '\n') {
			is_changed = 1;
			goto a;
		}
	}
	if (ins_mem (1))
a:		text[cur_pos++] = ch;
}

void	k_copyblock (void)
{
	if (eos_pos <= bos_pos || (cur_pos > bos_pos && cur_pos < eos_pos))
		beep ();
	else if (ins_mem (eos_pos - bos_pos))
		strncpy (text + cur_pos, text + bos_pos, eos_pos - bos_pos);
}

void	k_moveblock (void)
{
	int	i;

	if (eos_pos <= bos_pos || (cur_pos > bos_pos && cur_pos < eos_pos)) {
		beep ();
		return;
	}
	k_copyblock ();
	i = eos_pos - bos_pos;
	del_mem (bos_pos, i);
	bos_pos = cur_pos;
	eos_pos = cur_pos + i;
}

void	k_deleteblock (void)
{
	if (eos_pos <= bos_pos)
		beep ();
	else
		del_mem (bos_pos, eos_pos - bos_pos);
}

int	find_again (int flag)
{
	int	f_len, i;

	f_len = strlen (find_str);
	if (!f_len)
		return 0;
	for (i = cur_pos + flag; i <= eof_pos - f_len; i++)
		if (!strncmp (text + i, find_str, f_len))
			break;
	if (i > eof_pos - f_len)
		beep ();
	else
		cur_pos = i;
	return i <= eof_pos - f_len;
}

int	k_find (void)
{
	if (!enter_string ("Search for: ", find_str) || !*find_str)
		return 0;
	find_mode = 1;
	return find_again (0);
}

void	replace_again (void)
{
	int	i;

	if (!find_again (0))
		return;
	del_mem (cur_pos, strlen (find_str));
	if (!*replace_str)
		return;
	i = strlen (replace_str);
	if (ins_mem (i)) {
		strncpy (text + cur_pos, replace_str, i);
		cur_pos += i;
	}
}

void	k_replace (void)
{
	if (!k_find ())
		return;
	if (!enter_string ("Replace to: ", replace_str))
		return;
	find_mode = 0;
	replace_again ();
}

void	k_again (void)
{
	if (find_mode)
		find_again (1);
	else
		replace_again ();
}

int	load (char *name)
{
	FILE	*f;
	int	i;

	f = fopen (name, "r");
	if (!f)
		return error ("$load file \"%s\"", name);
	if (fseek (f, 0, SEEK_END))
		return error ("$seek");
	i = ftell (f);
	if (ins_mem (i)) {
		if (fseek (f, 0, SEEK_SET))
			return error ("$seek");
		if ((int)fread (text + cur_pos, 1, i, f) < i)
			return error ("$read");
	} else
		i = 0;
	fclose (f);
	return i;
}

int	save (char *name, int pos, int size)
{
	FILE	*f;

	f = fopen (name, "w");
	if (!f)
		return error ("$save file \"%s\"", name);
	if ((int)fwrite (text + pos, 1, size, f) < size)
		return error ("$write");
	if (fclose (f))
		return error ("$close");
	return 1;
}

void k_save(void)
{
	if (!enter_string ("Enter file name to save: ", file_name))
		return;
	if (save (file_name, 0, eof_pos))
		is_changed = 0;
}

void	k_getblock (void)
{
	if (!enter_string ("Enter file name to load block: ", block_name))
		return;
	eos_pos = load (block_name) + cur_pos;
	bos_pos = cur_pos;
}

void	k_putblock (void)
{
	if (bos_pos >= eos_pos)
		return;
	if (!enter_string ("Enter file name to save block: ", block_name))
		return;
	save (block_name, bos_pos, eos_pos - bos_pos);
}

void	goto_line (int l)
{
	for (cur_pos = 0; --l > 0 && cur_pos < eof_pos;)
		cur_pos = nextline (cur_pos);
}

void	k_goto (void)
{
	char	buf[STRMAX];

	*buf = 0;
	if (!enter_string ("Goto line: ", buf))
		return;
	if (*buf)
		goto_line (atoi (buf));
	else
		cur_pos = bos_pos;
}

void	done (int sig)
{
	(void)sig;
	endwin ();
	exit (0);
}

void init (void)
{
	signal (SIGINT, done);
	initscr();
	keypad (stdscr, TRUE);
	//scrollok(stdscr, TRUE);
	//idlok(stdscr, TRUE);
	//nonl();
	//removed: raw ();
	//noecho();
}

void norm_cur(void)
{
	int i;
	cur_line = bol (cur_pos);
	while (cur_line < bow_line)
		bow_line = prevline (bow_line);
	cur_y = 0;
	for (i = bow_line; i < cur_line; i = nextline (i))
		cur_y++;
	for (; cur_y >= rowmax; cur_y--)
		bow_line = nextline (bow_line);
	cur_x = win_x (cur_line, cur_pos - cur_line) - win_shift;
	while (cur_x < 0) {
		cur_x += TABSIZE;
		win_shift -= TABSIZE;
	}
	while (cur_x >= COLS) {
		cur_x -= TABSIZE;
		win_shift += TABSIZE;
	}
}











//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
int main (int argv, char **argc)
{
  int i, ch;
  if ( strcmp( file_name, "" ) == 0 )   strncpy( file_name, "noname.c" , STRMAX );
  // init();
  //initscr();	
	signal (SIGINT, done);
	initscr ();
	keypad (stdscr, TRUE);
	scrollok (stdscr, TRUE);
	idlok (stdscr, TRUE);
	nonl ();
	// raw ();
	noecho ();

           //curs_set( 0 );
           noecho();            
           keypad( stdscr, TRUE );  // for F...
           start_color();
           init_pair(0,  COLOR_WHITE,     COLOR_BLACK);
           init_pair(1,  COLOR_RED,     COLOR_BLACK);
           init_pair(2,  COLOR_GREEN,   COLOR_BLACK);
           init_pair(3,  COLOR_YELLOW,  COLOR_BLACK);
           init_pair(4,  COLOR_BLUE,    COLOR_BLACK);
           init_pair(5,  COLOR_MAGENTA, COLOR_BLACK);
           init_pair(6,  COLOR_CYAN,    COLOR_BLACK);
           init_pair(7,  COLOR_BLUE,    COLOR_WHITE);
           init_pair(8,  COLOR_WHITE,   COLOR_RED);
           init_pair(9,  COLOR_BLACK,   COLOR_GREEN);
           init_pair(10, COLOR_BLUE,  COLOR_YELLOW   );
           init_pair(11, COLOR_WHITE,   COLOR_BLUE);
           init_pair(12, COLOR_YELLOW,   COLOR_BLUE);
           init_pair(13, COLOR_BLACK,   COLOR_CYAN);
           init_pair(14, COLOR_BLUE,   COLOR_GREEN);
           init_pair(15, COLOR_BLUE, COLOR_CYAN );
           init_pair(16, COLOR_CYAN, COLOR_WHITE );
           init_pair(17, COLOR_CYAN, COLOR_YELLOW );
           init_pair(18, COLOR_CYAN, COLOR_BLUE);
           init_pair( 19, COLOR_MAGENTA , COLOR_BLUE);
           init_pair( 20 , COLOR_RED , COLOR_BLUE);
           init_pair( 21 , COLOR_BLUE , COLOR_YELLOW);
           init_pair( 22, COLOR_YELLOW,   COLOR_CYAN);
           init_pair( 23, COLOR_WHITE, COLOR_BLUE);
           init_pair( 24,  COLOR_GREEN, COLOR_BLUE);
           init_pair( 25 , COLOR_YELLOW , COLOR_BLUE);
           init_pair( 26 , COLOR_BLUE , COLOR_YELLOW);

	if (argv >= 2) {
		strncpy (file_name, argc[1], STRMAX - 1);
		file_name[STRMAX - 1] = 0;
		load (file_name);
		is_changed = 0;
	}

        getmaxyx( stdscr, rows , cols);
        clearscreen();
        color_c2();
        mvcenter( rows/2 , "MEDIT: The Unimark Editor" );
        getch();
        

	//for (;;) 
        int gameover = 0;
        while( gameover == 0 ) 
        {
                ///////// level 0
                getmaxyx( stdscr, rows , cols);
                rowmax = rows-4;
                curs_set( 1 );
                ///////// level 1
                //color_set( 11, NULL ); attroff( A_BOLD ); attroff( A_REVERSE );
                clearscreen();
                ///////// level 2
		show();

                ///////// level 5
                showstatus();

		move(cur_y -SHIFTY+4 , cur_x +SHIFTX);
		refresh ();
		ch = getch ();
		switch (ch) {

		case KEY_F(10):
			gameover = 1;
			break;

		case KEY_F(9):
		case KEY_F(1):
			editor_menu_beon();
			break;

		case KEY_UP:
			k_up ();
			break;

		case KEY_DOWN:
			k_down ();
			break;
		case KEY_LEFT:
			if (cur_pos)
				cur_pos--;
			break;
		case KEY_RIGHT:
			if (cur_pos < eof_pos)
				cur_pos++;
			break;
		case KEY_PPAGE: case CTRL ('J'):
			for (i = 1; i < rowmax; i++)
				k_up ();
			break;
		case KEY_NPAGE: case CTRL ('K'):
			for (i = 1; i < rowmax; i++)
				k_down ();
			break;
		case KEY_DC:	/* del */
			if (cur_pos < eof_pos)
				del_mem (cur_pos, 1);
			break;
		case KEY_BACKSPACE:
			if (cur_pos)
				del_mem (--cur_pos, 1);
			break;
		case KEY_HOME:
			cur_pos = cur_line;
			break;
		case KEY_END:
			cur_pos = eol (cur_pos);
			break;
		case CTRL ('X'):
			if (!is_changed || confirm ("Discard changes and exit? (y/N):"))
				done (0);
			break;
		case CTRL ('T'):	/* go Top */
			bow_line = cur_pos = 0;
			break;
		case CTRL ('O'):	/* go bOttom */
			cur_pos = eof_pos;
			break;
		case CTRL ('Y'):	/* del line */
			del_mem (cur_line, nextline (cur_line) - cur_line);
			break;
		case CTRL ('B'):	/* mark Begin of block */
			bos_pos = cur_pos;
			break;
		case CTRL ('E'):	/* mark End of block */
			eos_pos = cur_pos;
			break;
		case CTRL ('Q'):	/* Quote char */
			ins_ch (getch ());
			break;
		case CTRL ('C'):
			k_copyblock ();
			break;
		case CTRL ('D'):
			k_deleteblock ();
			break;
		case CTRL ('V'):
			k_moveblock ();
			break;

		case KEY_F(2):
			color_c2();
			k_save();
			break;

		case KEY_F(3):
			color_c2();
			break;


		case KEY_F(5):
			color_c2();
                        if ( fexist( file_name ) == 1 ) make_c( file_name );
			break;

		case KEY_F(6):
                        if ( color_scheme == 1 ) color_scheme = 2; 
                        else color_scheme = 1;
			break;

		case KEY_F(11):
			color_c2();
			toxin--;
			break;
		case KEY_F(12):
			color_c2();
			toxin++;
			break;

		case CTRL ('F'):
			k_find ();
			break;

		case CTRL ('R'):
			k_replace ();
			break;
		case CTRL ('N'):
			k_again ();
			break;
		case CTRL ('P'):
			k_putblock ();
			break;
		case CTRL ('G'):
			k_getblock ();
			break;
		case KEY_IC:
			ins_mode ^= 1;
			break;
		case CTRL ('A'):
			k_goto ();
			break;
		case '\r':
			ch = '\n';
			/* FALLTHRU */
		default:
			if (!iscntrl (ch) || ch == '\t' || ch == '\n')
				ins_ch (ch);
			else
				beep ();
			break;
		}
		norm_cur ();
	}
	/* NOTREACHED */


      endwin();
      printf( "mtvedit: bye \n" );
      return 0;
}



