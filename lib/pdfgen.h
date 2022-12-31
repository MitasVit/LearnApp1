#include <cairo/cairo.h>
#include <string>
#include <vector>
#include <cmath>
#include <cairo/cairo-pdf.h>
#include <cairo/cairo-svg.h>
#include <cairo/cairo-gobject.h>
#include <cairo/cairo-ps.h>
#include <cairo/cairo-ft.h>
#include <pango-1.0/pango/pango.h>
#include <pango-1.0/pango/pangocairo.h>

using namespace std;

class PDFGen
{
public:
    cairo_t *cr_;
    cairo_surface_t *surface_;

    PDFGen(const std::string &pdffile, double width, double height)
    {
        surface_ = cairo_pdf_surface_create(pdffile.c_str(), width, height);
        cr_ = cairo_create(surface_);
    }

    ~PDFGen()
    {
        cairo_destroy(cr_);
        cairo_surface_destroy(surface_);
    }

    void add_text(double x, double y, const std::string &text, double font_size, const std::string &font_face)
    {
        cairo_select_font_face(cr_, font_face.c_str(), CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr_, font_size);
        cairo_move_to(cr_, x, y);
        cairo_show_text(cr_, text.c_str());
    }

    void add_image(double x, double y, const std::string &imgfile)
    {
        cairo_surface_t *image = cairo_image_surface_create_from_png(imgfile.c_str());
        cairo_set_source_surface(cr_, image, x, y);
        cairo_paint(cr_);
        cairo_surface_destroy(image);
    }

    void add_shape(double x, double y, double width, double height)
    {
        cairo_rectangle(cr_, x, y, width, height);
        cairo_stroke(cr_);
    }
    void add_svg(double x, double y, std::string filename)
    {
        // Load SVG image as Cairo surface
        cairo_surface_t *svg_surface = cairo_svg_surface_create(filename.c_str(), 8.5, 11.0);

        // Draw SVG image to PDF
        cairo_set_source_surface(cr_, svg_surface, x, y);
        cairo_paint(cr_);

        cairo_surface_destroy(svg_surface);
    }

    void save_pdf()
    {
        cairo_status_t status = cairo_surface_status(surface_);
        if (status != CAIRO_STATUS_SUCCESS)
        {
            // Handle error
        }
        else
        {
            cairo_show_page(cr_);
            cairo_surface_finish(surface_);
        }
    }
    void add_circle(double x, double y, double radius)
    {
        cairo_arc(cr_, x, y, radius, 0.0, 2.0 * M_PI);
        cairo_stroke(cr_);
    }
    void add_arc(double x, double y, double radius, double start_angle, double end_angle)
    {
        cairo_arc(cr_, x, y, radius, start_angle, end_angle);
        cairo_stroke(cr_);
    }

    void add_page()
    {
        cairo_show_page(cr_);
    }
    void add_polygon(const std::vector<std::pair<double, double>> &vertices)
    {
        cairo_move_to(cr_, vertices[0].first, vertices[0].second);
        for (size_t i = 1; i < vertices.size(); ++i)
        {
            cairo_line_to(cr_, vertices[i].first, vertices[i].second);
        }
        cairo_close_path(cr_);
        cairo_stroke(cr_);
    }
    void add_roundfilledrect(double x, double y, double width, double height, double radius)
    {
        double x1 = x + radius;
        double y1 = y + radius;
        double x2 = x + width - radius;
        double y2 = y + height - radius;

        cairo_move_to(cr_, x1, y);
        cairo_arc(cr_, x2, y1, radius, -90.0 * (M_PI / 180.0), 0.0 * (M_PI / 180.0));
        cairo_arc(cr_, x2, y2, radius, 0.0 * (M_PI / 180.0), 90.0 * (M_PI / 180.0));
        cairo_arc(cr_, x1, y2, radius, 90.0 * (M_PI / 180.0), 180.0 * (M_PI / 180.0));
        cairo_arc(cr_, x, y1, radius, 180.0 * (M_PI / 180.0), 270.0 * (M_PI / 180.0));
        cairo_close_path(cr_);
        cairo_fill(cr_);
    }
    void add_latex(double x, double y, std::string latex)
    {
        // Create Pango layout
        PangoLayout *layout = pango_cairo_create_layout(cr_);
        pango_layout_set_markup(layout, latex.c_str(), -1);

        // Set font and font size
        PangoFontDescription *font_desc = pango_font_description_from_string("DejaVu Sans Mono");
        pango_font_description_set_size(font_desc, 10 * PANGO_SCALE);
        pango_layout_set_font_description(layout, font_desc);
        pango_font_description_free(font_desc);

        // Set position of layout
        pango_layout_set_alignment(layout, PANGO_ALIGN_LEFT);
        pango_layout_set_width(layout, 400 * PANGO_SCALE);
        cairo_move_to(cr_, x, y);
        pango_cairo_update_layout(cr_, layout);
        pango_cairo_show_layout(cr_, layout);

        // Clean up
        g_object_unref(layout);
    }
    struct Color
    {
        double r;
        double g;
        double b;
    };
    struct TextSegment
    {
        std::string text;
        Color color;
    };

    void add_colortext(double x, double y, std::string font, double font_size, std::vector<TextSegment> segments)
    {
        // Load font
        FT_Face face;
        cairo_font_face_t *font_face = cairo_ft_font_face_create_for_ft_face(face, 0);
        cairo_set_font_face(cr_, font_face);

        // Set font size
        cairo_set_font_size(cr_, font_size);

        // Draw text segments with different colors
        for (const TextSegment &segment : segments)
        {
            // Set text color
            cairo_set_source_rgb(cr_, segment.color.r, segment.color.g, segment.color.b);

            // Draw text segment
            cairo_move_to(cr_, x, y);
            cairo_show_text(cr_, segment.text.c_str());

            // Update text position
            cairo_text_extents_t extents;
            cairo_text_extents(cr_, segment.text.c_str(), &extents);
            x += extents.x_advance;
        }

        // Clean up
        cairo_font_face_destroy(font_face);
    }
    void add_metadata(std::string title, std::string author, std::string subject, string createdate, string moddate)
    {
        cairo_pdf_surface_set_metadata(surface_, cairo_pdf_metadata_t::CAIRO_PDF_METADATA_AUTHOR, author.c_str());
        cairo_pdf_surface_set_metadata(surface_, cairo_pdf_metadata_t::CAIRO_PDF_METADATA_SUBJECT, subject.c_str());
        cairo_pdf_surface_set_metadata(surface_, cairo_pdf_metadata_t::CAIRO_PDF_METADATA_TITLE, title.c_str());
        cairo_pdf_surface_set_metadata(surface_, cairo_pdf_metadata_t::CAIRO_PDF_METADATA_MOD_DATE, moddate.c_str());
        cairo_pdf_surface_set_metadata(surface_, cairo_pdf_metadata_t::CAIRO_PDF_METADATA_CREATE_DATE, createdate.c_str());
    }
};
