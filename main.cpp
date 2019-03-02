#include <fcntl.h>
#include <getopt.h>
#include <locale.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <array>
#include <atomic>
#include <condition_variable>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <mutex>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <utility>
#include <functional>
#include <ctime>
#include <cmath>
#include <curses.h>
#include <cdk.h>
#include </usr/include/menu.h>
#include <dirent.h>
#include <cstdio>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 5


using namespace std;


char* menu_choices[]{"Continue", "New", "Settings", "More", "About", "Exit"};
struct dirent64** dir_list;
int row, col;


void ncurses_testing();
void cdk_menu_test();
void ncurses_menu_test();
void ncurses_bind_test();
void cdk_label_test();
static int dialogHelpCB (EObjectType cdktype, void*, void*, chtype key);
void cdk_dialog_test();
void ncurses_title_screen();
void cdk_viewer_test();
void cdk_label_test();



int main(int argc, char** argv){
  
  
  int i;
  cin >> i;
  cdk_viewer_test();
  //ncurses_menu_test();
  //cdk_dialog_test();
  //ncurses_title_screen();
  return 0;
  
}











void ncurses_title_screen(){

  int x, y, c, n_choices;
  float               percentage{15.0f};
  unsigned long long* file_pointer_position = new unsigned long long;
  *file_pointer_position = 45555338862;
  unsigned long long  offset_end = 65555338862;


  getmaxyx(stdscr, row, col);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_GREEN);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  char* title = "F I L E  C A R V E R";
  WINDOW* win = newwin(row, col, y, x);

  //lock_guard<mutex> q_lck(queue_lck);
  while(percentage < 100){

    getyx(win, y, x);
    ostringstream  curses_test{};
    this_thread::sleep_for(500ms);
    
      
      mvprintw(row/2 -3, (col-strlen(title))/2, "%s", title);
      mvchgat(row/2 -3, (col-strlen(title))/2-1, strlen(title) + 2,
              A_STANDOUT, 1, NULL);

      curses_test << *file_pointer_position<< " / "  << offset_end;

      mvprintw(row/2 - 1, (col-strlen(curses_test.str().c_str()))/2,
               "%s", curses_test.str().c_str());

      mvchgat(row/2 - 1, (col-strlen(curses_test.str().c_str()))/2-1,
      curses_test.str().size()+2, A_STANDOUT, 3, NULL);


      mvprintw(row/2 + 3, (col-2)/2, "%d\%", percentage);
      mvchgat(row/2 + 3, (col-2)/2-1, 6, A_STANDOUT, 3, NULL);
      printw("X: %d, Y: %d", x, y);

      refresh();
  }
}





void ncurses_menu_test() {

  
  int x, y, c, n_choices;
  

  ITEM** my_items;
  MENU*  my_menu;
  ITEM*  current_item;

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  n_choices = ARRAY_SIZE(menu_choices);
  my_items = (ITEM**)calloc(n_choices+1, sizeof(ITEM*));
  
  for(int i = 0; i < n_choices; ++i)
    my_items[i] = new_item(menu_choices[i], menu_choices[i]);

  my_items[n_choices] = (ITEM*)NULL;
  my_menu = new_menu((ITEM**)my_items);
  mvprintw(LINES-2, 0, "F1 to Exit");
  post_menu(my_menu);
  refresh();

  while((c = getch()) != KEY_F(1)){
    switch(c){
      case KEY_DOWN:
        menu_driver(my_menu, REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver(my_menu, REQ_UP_ITEM);
        break;
    }
  }
  free_item(my_items[0]);
  free_item(my_items[1]);
  free_menu(my_menu);
  endwin();

  

}






  
#ifdef HAVE_XCURSES
  char *XCursesProgramName="bind_ex";
  #endif

static int dialogHelpCB (EObjectType cdktype GCC_UNUSED, void *object, void *clientData GCC_UNUSED, chtype key GCC_UNUSED)
{
  CDKDIALOG *dialog = (CDKDIALOG *)object;
  char *mesg[5];

  /* Check which button we are on. */
  if (dialog->currentButton == 0)
  {
    mesg[0] = "<C></U>Help for </U>Who<!U>.";
    mesg[1] = "<C>When this button is picked the name of the current";
    mesg[2] = "<C>user is displayed on the screen in a popup window.";
    popupLabel (ScreenOf(dialog), mesg, 3);
  }
  else if (dialog->currentButton == 1)
  {
    mesg[0] = "<C></U>Help for </U>Time<!U>.";
    mesg[1] = "<C>When this button is picked the current time is";
    mesg[2] = "<C>displayed on the screen in a popup window.";
    popupLabel (ScreenOf(dialog), mesg, 3);
  }
  else if (dialog->currentButton == 2)
  {
    mesg[0] = "<C></U>Help for </U>Date<!U>.";
    mesg[1] = "<C>When this button is picked the current date is";
    mesg[2] = "<C>displayed on the screen in a popup window.";
    popupLabel (ScreenOf(dialog), mesg, 3);
  }
  else if (dialog->currentButton == 3)
  {
    mesg[0] = "<C></U>Help for </U>Quit<!U>.";
    mesg[1] = "<C>When this button is picked the dialog box is exited.";
    popupLabel (ScreenOf(dialog), mesg, 2);
  }
  return (FALSE);
}











void cdk_dialog_test() {

  /* Declare variables. */
  CDKSCREEN     *cdkscreen;
  CDKDIALOG     *question;
  char          *buttons[40];
  char          *message[40], *info[5], *loginName;
  char          temp[256];
  int           selection;
  time_t        clck;
  struct tm     *currentTime;

  cdkscreen = initCDKScreen (NULL);

  /* Start color. */
  initCDKColor();

  /* Set up the dialog box. */
  message[0] = "<C></U>Simple Command Interface";
  message[1] = "Pick the command you wish to run.";
  message[2] = "<C>Press </R>?<!R> for help.";
  buttons[0] = "Who";
  buttons[1] = "Time";
  buttons[2] = "Date";
  buttons[3] = "Quit";

  // Create the dialog box
  question = newCDKDialog (cdkscreen, CENTER, CENTER,
                           message, 3, buttons, 4, A_REVERSE,
                           TRUE, TRUE, FALSE);

  // Check if we got a null value back
  if (question == (CDKDIALOG *)0) {
    destroyCDKScreen (cdkscreen);

    // End curses...
    endCDK();

    // Spit out a message
    printf ("Oops. Can't seem to create the dialog box. Is the window too small?\n");
    exit (1);
  }

  // Create the key binding
  bindCDKObject (vDIALOG, question, '?', dialogHelpCB, 0);

  //Activate the dialog box
  selection = 0;
  while (selection != 3) {
    // Get the users button selection
    selection = activateCDKDialog (question, (chtype *)0);

    // Check the results
    if (selection == 0) {
      // Get the users login name
      info[0]   = "<C>     </U>Login Name<!U>     ";
      loginName = getlogin();
      
      if (loginName == (char *)0) 
        strcpy (temp, "<C></R>Unknown");
      
      else
        sprintf (temp, "<C><%s>", loginName);
      
      info[1] = copyChar (temp);
      popupLabel (ScreenOf(question), info, 2);
      freeChar (info[1]);
    }
    else if (selection == 1) {
      // Print out the time
      time(&clck);
      currentTime = localtime(&clck);
      sprintf (temp, "<C>%d:%d:%d", currentTime->tm_hour,
                                    currentTime->tm_min,
                                    currentTime->tm_sec);
      info[0] = "<C>   </U>Current Time<!U>   ";
      info[1] = copyChar (temp);
      popupLabel (ScreenOf(question), info, 2);
      freeChar (info[1]);
    }
    else if (selection == 2) {
      // Print out the date
      time(&clck);
      currentTime = localtime(&clck);
      sprintf (temp, "<C>%d/%d/%02d", currentTime->tm_mday,
                                      currentTime->tm_mon,
                                      currentTime->tm_year % 100);
      info[0] = "<C>   </U>Current Date<!U>   ";
      info[1] = copyChar (temp);
      popupLabel (ScreenOf(question), info, 2);
      freeChar (info[1]);
    }
  }

  // Clean up
  destroyCDKDialog (question);
  destroyCDKScreen (cdkscreen);
  endCDK();
  exit (0);
  
}








void cdk_menu_test() {

  cout << "\nhello" << endl;
  CDKSCREEN* cdkscreen;
  
  char*     test_objs[4];

  cdkscreen = initCDKScreen(NULL);
  initCDKColor();


  test_objs[0] = "</31> First color tested string. <!31>";
  test_objs[1] = "</05> Second color tested string. <!05>";
  test_objs[2] = "</26> Third color tested string. <!26>";
  test_objs[3] = "<C> Default color tested string.";

  CDKLABEL* demo = newCDKLabel(cdkscreen, CENTER, CENTER, test_objs, 4, TRUE, TRUE);

  drawCDKLabel(demo, TRUE);
  waitCDKLabel(demo, ' ');

  int l = getch();
  
  destroyCDKLabel(demo);
  destroyCDKScreen(cdkscreen);
  endCDK();
  exit(1);


  char* msg = "Testing NCURSES BOIII";


  ostringstream dir_list_ss;
  int list_count = 0;
  int biggest = 0;
  int n = scandir64("/dev", &dir_list, NULL, alphasort64);
  cout << "Directory List:\n\t";

  while(n--) {

    dir_list_ss << "\t" << dir_list[n]->d_name << " ";

    if (n%5==0)
      dir_list_ss << "\n";

    biggest = (strlen(dir_list[n]->d_name) > biggest ?
                strlen(dir_list[n]->d_name) : biggest);
    ++list_count;
  }

  initscr();
  getmaxyx(stdscr, row, col);
  mvprintw(row/2-(list_count/2) > 0 ? (row/2-list_count/2) : 
              1, (col/2)-(biggest/2), "%s", dir_list_ss.str().c_str());
  char* usr_msg = "PRESS ANY KEY TO CONTINUE";
  mvprintw(row-2, (col/2)-strlen(usr_msg)/2, "%s", usr_msg);

}








void cdk_viewer_test() {

  CDK_CONST char* testy[35];
  testy[0] = "<C>/****************************************************************************";
  testy[1] = "<C>* Copyright (c) 1998-2016,2017 Free Software Foundation, Inc.              *";
  testy[2] = "<C>*                                                                          *";
  testy[3] = "<C>* Permission is hereby granted, free of charge, to any person obtaining a  *";
  testy[4] = "<C>* copy of this software and associated documentation files (the            *";
  testy[5] ="<C>*  \"Software\", to deal in the Software without restriction, including      *";
  testy[6] = "<C>* without limitation the rights to use, copy, modify, merge, publish,      *";
  testy[7] = "<C>* distribute, distribute with modifications, sublicense, and/or sell       *";
  testy[8] = "<C>* copies of the Software, and to permit persons to whom the Software is    *";
  testy[9] = "<C>* furnished to do so, subject to the following conditions:                 *";
 testy[10] = "<C>*                                                                          *";
 testy[11] = "<C>* The above copyright notice and this permission notice shall be included  *";
 testy[12] = "<C>* in all copies or substantial portions of the Software.                   *";
 testy[13] = "<C>*                                                                          *";
 testy[14] ="<C>*  THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS *";
 testy[15] = "<C>* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *";
 testy[16] = "<C>* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *";
 testy[17] = "<C>* IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *";
 testy[18] = "<C>* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *";
 testy[19] = "<C>* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *";
 testy[20] = "<C>* THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *";
 testy[21] = "<C>*                                                                          *";
 testy[22] = "<C>* Except as contained in this notice, the name(s) of the above copyright   *";
 testy[23] = "<C>* holders shall not be used in advertising or otherwise to promote the     *";
 testy[24] = "<C>* sale, use or other dealings in this Software without prior written       *";
 testy[25] = "<C>* authorization.                                                           *";
 testy[26] = "<C>****************************************************************************/";
 testy[27] = "\n";
 testy[28] = "\n";
 testy[29] = "<C>/****************************************************************************";
 testy[30] = "<C>*  Author: Zeyd M. Ben-Halim <zmbenhal@netcom.com> 1992,1995               *";
 testy[31] = "<C>*     and: Eric S. Raymond <esr@snark.thyrsus.com>                         *";
 testy[32] = "<C>*     and: Thomas E. Dickey                        1996-on                 *";
 testy[33] = "<C>****************************************************************************/";
 testy[34] = " ";

  CDKSCREEN* cdkscreen;
  CDKVIEWER* cdkviewer;
  char*      buttons[40];

  buttons[0] = "Button 1";
  buttons[1] = "<F=main.cpp><C>Source Code";
  buttons[2] = "Quit";


  cdkscreen = initCDKScreen(NULL);
  initCDKColor();
  
  cdkviewer = newCDKViewer(cdkscreen, CENTER, CENTER, 
                                      45, strlen(testy[10])+16, buttons, 
                                      3, A_REVERSE, TRUE, TRUE);
  
  
  setCDKViewerBackgroundColor(cdkviewer, NULL);                                      
  
  if (!cdkviewer) {
    destroyCDKScreen(cdkscreen);
    endCDK();
    printf("\nCould not open viewer... Exiting...");
    exit(1);
  }   
  char* file = selectFile(cdkscreen, "/home/adam/git/");
  setCDKViewer(cdkviewer, "Test Viewer", testy, 
               35, A_REVERSE, TRUE, TRUE, TRUE);      
  activateCDKViewer(cdkviewer, NULL); 
   
  cdkscreen->window->_scroll = TRUE;
  cdkviewer->obj.acceptsFocus = TRUE;
  
  viewFile(cdkscreen, "Scalpel.txt", "/home/adam/scalpel.txt", NULL, NULL);
  //refresh();                        
  viewFile(cdkscreen, "Main.cpp", "/home/adam/git/ncurses_experimentation/main.cpp", NULL, NULL);
  viewFile(cdkscreen, "Selected File", file, NULL, NULL);
}