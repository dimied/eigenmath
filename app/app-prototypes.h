void cmdisplay(void);
int count_denominators(struct atom *p);
void draw_char(float x, float y, int font_num, int char_num);
void draw_formula(float x, float y, float *p);
void draw_line(int x1, int y1, int x2, int y2);
void draw_selection_rect(float x, float y, float width, float height);
void draw_stroke(float x1, float y1, float x2, float y2, float stroke_width);
void draw_text(int font, int x, int y, uint8_t *s, int len, int color);
void emit_args(struct atom *p);
void emit_base(struct atom *p);
void emit_delims(double x, double y, double h, double d, double w, double stroke_width, int font_num);
void emit_denominators(struct atom *p);
void emit_double(struct atom *p);
void emit_draw(double x, double y, struct atom *p);
void emit_exponent(struct atom *p);
void emit_expr(struct atom *p);
void emit_expr_nib(struct atom *p);
void emit_factor(struct atom *p);
void emit_frac(struct atom *p);
void emit_function(struct atom *p);
void emit_indices(struct atom *p);
void emit_infix_operator(int c);
void emit_italic_char(int char_num);
void emit_italic_string(char *s);
void emit_left_delim(double x, double y, double h, double d, double w, double stroke_width);
void emit_list(struct atom *p);
void emit_matrix(struct atom *p, int d, int k);
void emit_medium_space(void);
void emit_numerators(struct atom *p);
void emit_numeric_exponent(struct atom *p);
void emit_power(struct atom *p);
void emit_push(double d);
void emit_rational(struct atom *p);
void emit_reciprocal(struct atom *p);
void emit_right_delim(double x, double y, double h, double d, double w, double stroke_width);
void emit_roman_char(int char_num);
void emit_roman_string(char *s);
void emit_string(struct atom *p);
void emit_subexpr(struct atom *p);
void emit_symbol(struct atom *p);
int emit_symbol_fragment(char *name, int k);
void emit_table(double x, double y, struct atom *p);
void emit_tensor(struct atom *p);
void emit_term(struct atom *p);
void emit_term_nib(struct atom *p);
void emit_thick_space(void);
void emit_thin_space(void);
void emit_update_fraction(void);
void emit_update_list(int t);
void emit_update_subexpr(void);
void emit_update_subscript(void);
void emit_update_superscript(void);
void emit_update_table(int n, int m);
void emit_vector(struct atom *p);
void eval_draw(void);
void draw_main(void);
void check_for_parametric_draw(void);
void create_point_set(void);
void new_point(double t);
void get_xy(double t);
void eval_f(double t);
void fill(int i, int j, int level);
void setup_trange(void);
void setup_trange_f(void);
void setup_xrange(void);
void setup_xrange_f(void);
void setup_yrange(void);
void setup_yrange_f(void);
void emit_graph(void);
CTFontRef get_font_ref(int font_num);
int get_ascent(int font_num);
int get_descent(int font_num);
int get_width(int font_num, int char_num);
int text_width(int font_num, char *s);
void get_height_width(int *h, int *w, int font_num, char *s);
void draw_point(int x, int dx, int y, int dy);
void draw_box(int x1, int y1, int x2, int y2);
double get_char_depth(int font_num, int char_num);
double get_char_height(int font_num);
CFStringRef get_char_name(int char_num);
double get_char_width(int font_num, int char_num);
double get_xheight(int font_num);
void init_fonts(void);
int isdenominator(struct atom *p);
void run_thread(char *s);
void * run_thread_nib(void *s);
void malloc_kaput(void);
void echo_input(char *s);
void printbuf(char *s, int color);
void printchar(int c, int color);
void shipout(struct display *p);
void clear_display(void);
int check_display(void);
void get_view(int *h, int *w);
void draw_display(int y1, int y2);
void eval_exit(void);
