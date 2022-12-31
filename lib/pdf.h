#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-page-renderer.h>
#include <poppler/cpp/poppler-image.h>
#include <cairo.h>
#include <string>

// Function to extract images from a PDF document
void extract_images(const std::string &pdffile, const std::string &folder) {
  // Load the PDF document
  poppler::document *doc = poppler::document::load_from_file(pdffile);
  poppler::page_renderer renderer;
  renderer.set_render_hint(poppler::page_renderer::antialiasing, true);
    renderer.set_render_hint(poppler::page_renderer::text_antialiasing, true);



  // Iterate over the pages in the document
  for (int i = 0; i < doc->pages(); ++i) {
    // Get the page
    poppler::page *page = doc->create_page(i);

    // Render the page to a Cairo surface
    int width = page->page_rect().width();
    int height = page->page_rect().height();
   // page->render(cr);
    //poppler:
    poppler::image img = renderer.render_page(page);
     std::string filename = folder + "/" + std::to_string(i) + ".png";
    // Create a Cairo surface
cairo_surface_t *surface = cairo_image_surface_create_for_data(
    (unsigned char*)img.data(), CAIRO_FORMAT_ARGB32, img.width(), img.height(), img.bytes_per_row());
// Save the Cairo surface to a file
cairo_surface_write_to_png(surface, filename.c_str());
// Clean up
cairo_surface_destroy(surface);

    delete page;
  }
}
