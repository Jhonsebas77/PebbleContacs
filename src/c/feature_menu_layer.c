#include "pebble.h"

#define NUM_MENU_SECTIONS 6
#define NUM_MENU_ICONS_MT1 1
#define NUM_MENU_ICONS_MT2 1
#define NUM_MENU_ICONS_MT3 1
#define NUM_MENU_ICONS_MT4 1
#define NUM_MENU_ICONS_MT5 1
#define NUM_MENU_ICONS_MT6 1
#define NUM_MENU_ICONS_MT7 1
#define NUM_MENU_ICONS_MT8 1
#define NUM_MENU_ICONS_MT9 1
#define NUM_FIRST_MENU_ITEMS 1
#define NUM_SECOND_MENU_ITEMS 4
#define NUM_THIRD_MENU_ITEMS 2
#define NUM_FOUR_MENU_ITEMS 6

static Window *s_main_window;
static MenuLayer *s_menu_layer;
static GBitmap *s_menu_icons1[NUM_MENU_ICONS_MT1];
static GBitmap *s_menu_icons2[NUM_MENU_ICONS_MT2];
static GBitmap *s_menu_icons3[NUM_MENU_ICONS_MT3];
static GBitmap *s_menu_icons4[NUM_MENU_ICONS_MT4];
static GBitmap *s_menu_icons5[NUM_MENU_ICONS_MT5];
static GBitmap *s_menu_icons6[NUM_MENU_ICONS_MT6];
static GBitmap *s_menu_icons7[NUM_MENU_ICONS_MT7];
static GBitmap *s_menu_icons8[NUM_MENU_ICONS_MT8];
static GBitmap *s_menu_icons9[NUM_MENU_ICONS_MT9];
static GBitmap *s_background_bitmap;

static int s_current_icon1 = 0;
static int s_current_icon2 = 0;
static int s_current_icon3 = 0;
static int s_current_icon4 = 0;
static int s_current_icon5 = 0;
static int s_current_icon6 = 0;
static int s_current_icon7 = 0;
static int s_current_icon8 = 0;
static int s_current_icon9 = 0;

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      return NUM_FIRST_MENU_ITEMS;
    case 1:
      return NUM_SECOND_MENU_ITEMS;
    case 2:
      return NUM_THIRD_MENU_ITEMS;
    case 3:
      return NUM_FOUR_MENU_ITEMS;
   default:
      return 0;
  }
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  // Determine which section we're working with
  switch (section_index) {
     case 0:
      // Draw title text in the section header
      menu_cell_basic_header_draw(ctx, cell_layer, ".: Mi Numero :.");
      break;
    case 1:
      // Draw title text in the section header
      menu_cell_basic_header_draw(ctx, cell_layer, ".: Familia :.");
      break;
    case 2:
      menu_cell_basic_header_draw(ctx, cell_layer, ".: Amigos :.");
      break;
    case 3:
      menu_cell_basic_header_draw(ctx, cell_layer, ".: Trabajo :.");
      break;
  }
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  switch (cell_index->section) {

        case 0:
      switch (cell_index->row) {
           case 0:
          // There is title draw for something more simple than a basic menu item
           menu_cell_basic_draw(ctx, cell_layer, "Sebastian Otalora", "(321) 720-9516", s_menu_icons9[s_current_icon1]);
        break;

      }
      break;
    case 1:
      switch (cell_index->row) {
        case 0:
          menu_cell_basic_draw(ctx, cell_layer, "Julian Otalora", "(310) 494-2518", s_menu_icons2[s_current_icon1]);
          break;
        case 1:
          menu_cell_basic_draw(ctx, cell_layer, "Monica Beltran", "(310) 536-8325", s_menu_icons3[s_current_icon2]);
          break;
        case 2:
          menu_cell_basic_draw(ctx, cell_layer, "Paula Otalora", "(321) 626-8693", s_menu_icons4[s_current_icon2]);
          break;
         case 3:
          menu_cell_basic_draw(ctx, cell_layer, "Daniela Gil", "(316) 342-3650", s_menu_icons1[s_current_icon1]);
          break;

      }
      break;
    case 2:
      switch (cell_index->row) {
          case 0:
        menu_cell_basic_draw(ctx, cell_layer, "Denny -Segura", "(318) 247-4490", s_menu_icons8[s_current_icon1]);
        break;
        case 1:
         menu_cell_basic_draw(ctx, cell_layer, "Sebastian Ochoa", "(316) 877-5880", s_menu_icons8[s_current_icon1]);
        break;
      }
    break;
     case 3:
      switch (cell_index->row) {
      case 0:
         menu_cell_basic_draw(ctx, cell_layer, "Jackson Melo", "(315) 550-3017", s_menu_icons6[s_current_icon1]);
          break;
        case 1:
         menu_cell_basic_draw(ctx, cell_layer, "Martha Melo", "(315) 582-5437", s_menu_icons5[s_current_icon1]);
          break;
        case 2:
         menu_cell_basic_draw(ctx, cell_layer, "Sebastian Otalora", "(320) 787-1383", s_menu_icons9[s_current_icon1]);
          break;
        case 3:
         menu_cell_basic_draw(ctx, cell_layer, "Monica Torres", "(318) 335-4552", s_menu_icons5[s_current_icon1]);
          break;
        case 4:
         menu_cell_basic_draw(ctx, cell_layer, "Yuli Garcia", "(318) 678-8969", s_menu_icons5[s_current_icon1]);
          break;
         case 5:
         menu_cell_basic_draw(ctx, cell_layer, "Diana Grisales", "(311) 355-1150", s_menu_icons5[s_current_icon1]);
          break;
      }
    break;

  }
}

static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  // Use the row to specify which item will receive the select action
  switch (cell_index->row) {
    // This is the menu item with the cycling icon
    case 1:
      // Cycle the icon
      s_current_icon1 = (s_current_icon1) % NUM_MENU_ICONS_MT1;
      s_current_icon2 = (s_current_icon2) % NUM_MENU_ICONS_MT2;
      s_current_icon3 = (s_current_icon3) % NUM_MENU_ICONS_MT3;
      s_current_icon4 = (s_current_icon4) % NUM_MENU_ICONS_MT4;
      s_current_icon5 = (s_current_icon5) % NUM_MENU_ICONS_MT5;
      s_current_icon6 = (s_current_icon6) % NUM_MENU_ICONS_MT6;
      s_current_icon7 = (s_current_icon7) % NUM_MENU_ICONS_MT7;
      s_current_icon8 = (s_current_icon8) % NUM_MENU_ICONS_MT8;
      s_current_icon9 = (s_current_icon9) % NUM_MENU_ICONS_MT9;

  // After changing the icon, mark the layer to have it updated
      layer_mark_dirty(menu_layer_get_layer(menu_layer));
      break;
  }

}

static void main_window_load(Window *window) {
  // Here we load the bitmap assets
  s_menu_icons1[0] = gbitmap_create_with_resource(RESOURCE_ID_ICON_NOVIA);
  s_menu_icons2[0] = gbitmap_create_with_resource(RESOURCE_ID_ICON_PADRE);
  s_menu_icons3[0] = gbitmap_create_with_resource(RESOURCE_ID_ICON_MADRE);
  s_menu_icons4[0] = gbitmap_create_with_resource(RESOURCE_ID_ICON_HERMANA);
  s_menu_icons5[0] = gbitmap_create_with_resource(RESOURCE_ID_ICON_FRUTI);
  s_menu_icons6[0] = gbitmap_create_with_resource(RESOURCE_ID_ICON_BOSS);
  s_menu_icons7[0] = gbitmap_create_with_resource(RESOURCE_ID_ICON_DENNY);
  s_menu_icons8[0] = gbitmap_create_with_resource(RESOURCE_ID_ICON_8A);
  s_menu_icons9[0] = gbitmap_create_with_resource(RESOURCE_ID_ICON_SISTEMAS);


  // And also load the background
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND_BRAINS);

  // Now we prepare to initialize the menu layer
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Create the menu layer
  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(s_menu_layer, window);

  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

static void main_window_unload(Window *window) {
  // Destroy the menu layer
  menu_layer_destroy(s_menu_layer);

  // Cleanup the menu icons
//   for (int i = 0; i < NUM_MENU_ICONS; i++) {
//     gbitmap_destroy(s_menu_icons[i]);
//   }

  gbitmap_destroy(s_background_bitmap);
}

static void init() {
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
