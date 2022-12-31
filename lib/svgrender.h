#include <cairo.h>
#include <cairo-svg.h>
#include <imgui/imgui.h>
#include <string>

class SVGRender {
 public:
  // Constructor
  SVGRender(const char *filename) : filename_(filename), x_(0), y_(0), width_(0), height_(0) {}

  // Load and parse the SVG file
  bool Load() {
    // Load the SVG file
    svg_surface_ = cairo_svg_surface_create(filename_.c_str(), 0, 0);
    cairo_svg_surface_restrict_to_version(svg_surface_, CAIRO_SVG_VERSION_1_2);
    cairo_status_t status = cairo_surface_status(svg_surface_);
    if (status != CAIRO_STATUS_SUCCESS) {
      // Handle error
      return false;
    }

    // Create a Cairo context to render to
    cr_ = cairo_create(svg_surface_);

    // Render the SVG file to the Cairo context
    cairo_paint(cr_);

    // Get the dimensions of the SVG
    width_ = cairo_image_surface_get_width(cairo_get_target(cr_));
    height_ = cairo_image_surface_get_height(cairo_get_target(cr_));

    return true;
  }

  // Set the position of the SVG on the screen
  void SetPosition(int x, int y) {
    x_ = x;
    y_ = y;
  }

  // Set the size of the SVG image
  void SetSize(int width, int height) {
    width_ = width;
    height_ = height;
  }

    // Render the SVG using ImGui
  void Render() {
    // Create an ImGui image from the Cairo surface
    ImTextureID texture_id = reinterpret_cast<ImTextureID>(cairo_get_target(cr_));
    ImGui::SetCursorPos(ImVec2(x_, y_));
    ImGui::Image(texture_id, ImVec2(width_, height_));
  }


  // Destructor
  ~SVGRender() {
    cairo_destroy(cr_);
    cairo_surface_destroy(svg_surface_);
  }

 private:
  std::string filename_;
  cairo_surface_t *svg_surface_;
  cairo_t *cr_;
  double width_;
  double height_;
  int x_;
  int y_;
};
