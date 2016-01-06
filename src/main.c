#include <pebble.h>

Window *window;
TextLayer *time_layer;
TextLayer *date_layer;
static BitmapLayer *s_bitmap_layer;
static GBitmap *s_example_bitmap;

void handle_timechanged(struct tm *tick_time, TimeUnits units_changed)
{
    static char time_buffer[10];
    strftime(time_buffer, sizeof(time_buffer),"%H:%M:%S",tick_time);
    text_layer_set_text(time_layer, time_buffer);
    static char date_buffer[10];
    strftime(date_buffer, sizeof(date_buffer),"%x",tick_time);
    text_layer_set_text(date_layer, date_buffer);
}
TextLayer* text_layerproperties(GRect frame)
{
		TextLayer* text_layer;
	  text_layer = text_layer_create(frame);
		text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS));
		text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
		// Add the text layer to the window
		layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
		return text_layer;
}
void handle_init(void) 
{
	// Create a window and text layer
	window = window_create();
	// Set the text, font, and text alignment
	time_layer = text_layerproperties(GRect(0, 0, 144, 154));
	date_layer = text_layerproperties(GRect(0, 137, 144, 154));
	
	
  tick_timer_service_subscribe(SECOND_UNIT, handle_timechanged);
  
  //Add the picture to the window
	
 
  s_example_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CAT_IMAGE_ID);

  s_bitmap_layer = bitmap_layer_create(GRect(5, 5, 144, 154));
	bitmap_layer_set_compositing_mode(s_bitmap_layer, GCompOpSet);
  bitmap_layer_set_bitmap(s_bitmap_layer, s_example_bitmap);
	
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bitmap_layer));
  

	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
	
}

void handle_deinit(void) 
{
	// Destroy the text layer
	//text_layer_destroy(text_layer);
	text_layer_destroy(time_layer);
  text_layer_destroy(date_layer);
  gbitmap_destroy(s_example_bitmap);
  bitmap_layer_destroy(s_bitmap_layer);
	// Destroy the window
	window_destroy(window);
}

int main(void) 
{
	
	handle_init();
	
	app_event_loop();
	handle_deinit();
}
