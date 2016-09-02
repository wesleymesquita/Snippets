#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>

/*BEGIN - CalculatorApp stuff*/

struct __CalculatorApp{
    int size_x;
    int size_y;
};

typedef struct __CalculatorApp CalculatorApp;

static CalculatorApp*
init_calculatorapp(int sx, int sy)
{
    CalculatorApp* c = (CalculatorApp*)malloc(sizeof(CalculatorApp));
    c->size_x = sx;
    c->size_y = sy;
    return c;
}

static void
destroy_calculatorapp(CalculatorApp* c)
{
    free(c);
} 

/*END - CalculatorApp Stuff*/

static void
click_button(GtkApplication* app, 
            gpointer data)
{
    printf("Hey, you have clicked in the button!!!\n");    
}




static void
click_button_save_data(GtkApplication* app,
                       gpointer data)

{
    const gchar* buf = gtk_entry_get_text((GtkEntry*)data);     
    g_print("I wrote : %s\n", (char*)buf);    
}


static void
init_widgets(GtkWidget* grid, CalculatorApp* calc){
/* -----------------  
 * |               |
 * -----------------
 *
 *  7   8    9   /
 *
 *  4   5    6   X 
 *
 *  1   2    3   -
 *
 *      0        +
 *
 * */


    /*1) Add expression entry*/
    GtkWidget* expr_entry;
    GtkWidget* expr_entry_buffer;
    expr_entry_buffer = gtk_entry_buffer_new((const gchar*)NULL, -1);    
    expr_entry  = gtk_entry_new_with_buffer((struct GtkEntryBuffer*)expr_entry_buffer);
    
    int entry_sz_pxl  = calc->size_x*0.8;
    gtk_entry_set_width_chars((GtkEntry*)expr_entry, entry_sz_pxl/8);
    
    gtk_fixed_put((GtkFixed*)grid, expr_entry, calc->size_x*0.05, 10);

/*2) Add the buttons*/
    GtkWidget* buttons[14];
    buttons[0] = gtk_button_new_with_label("0");
    buttons[1] = gtk_button_new_with_label("1");
    buttons[2] = gtk_button_new_with_label("2");
    buttons[3] = gtk_button_new_with_label("3");
    buttons[4] = gtk_button_new_with_label("4");
    buttons[4] = gtk_button_new_with_label("5");
    buttons[5] = gtk_button_new_with_label("6");
    buttons[6] = gtk_button_new_with_label("7");
    buttons[7] = gtk_button_new_with_label("8");
    buttons[8] = gtk_button_new_with_label("8");
    buttons[9] = gtk_button_new_with_label("9");
    buttons[10] = gtk_button_new_with_label("+");
    buttons[11] = gtk_button_new_with_label("-");
    buttons[12] = gtk_button_new_with_label("X");
    buttons[13] = gtk_button_new_with_label("/");

    
    gtk_fixed_put((GtkFixed*)grid, expr_entry, calc->size_x*0.05, 10);
    
}



static void
activate (GtkApplication* app,
          gpointer        user_data)
{
    
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *grid;  /*GTK Fixed*/  
    GtkWidget *phrase_entry;   

    CalculatorApp* calc;
    calc = (CalculatorApp*)user_data;
    

    /*setup window*/
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Calculate it!");
    gtk_window_set_default_size (GTK_WINDOW (window), 
                                calc->size_x, 
                                calc->size_y);

    
    grid = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    
    init_widgets(grid, calc);
               
    gtk_widget_show_all (window);
}

static void
go_down (GtkApplication* app, 
         gpointer user_data)
{
    printf("LOG :: App go shut down!");
    g_print("Thank you for using our app :)");
}

int
main (int    argc,
      char **argv)
{   
    GtkApplication *app;
    int status;

    CalculatorApp* calc;
    calc = init_calculatorapp(480, 480);

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), calc);
    g_signal_connect (app, "shutdown", G_CALLBACK (go_down), calc);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    
    destroy_calculatorapp(calc);

    return status;
}
