#include <memory>

#include <led-matrix.h>

namespace rgb = rgb_matrix;

static auto create_options() -> rgb::RGBMatrix::Options;
static void draw(rgb::Canvas* c);

int main() {
    const auto options = create_options();

    auto rt_options = rgb::RuntimeOptions();
    rt_options.gpio_slowdown = 5;

    auto matrix = std::unique_ptr<rgb::RGBMatrix>(rgb::CreateMatrixFromOptions(options, rt_options));
    draw(matrix.get());

    return 0;
}

static auto create_options() -> rgb::RGBMatrix::Options {
    auto options = rgb::RGBMatrix::Options();
    options.cols = 96;
    options.rows = 48;

    options.pwm_lsb_nanoseconds = 130;
    options.pwm_bits = 11;

    options.brightness = 100;

    return options;
}

static void draw(rgb::Canvas* c) {
    const int width = c->width() - 1;
    const int height = c->height() - 1;
    // Borders
    rgb::DrawLine(c, 0, 0, width, 0, rgb::Color(255, 0, 0));
    rgb::DrawLine(c, 0, height, width, height, rgb::Color(255, 255, 0));
    rgb::DrawLine(c, 0, 0, 0, height, rgb::Color(0, 0, 255));
    rgb::DrawLine(c, width, 0, width, height, rgb::Color(0, 255, 0));

    // Diagonals.
    rgb::DrawLine(c, 0, 0, width, height, rgb::Color(255, 255, 255));
    rgb::DrawLine(c, 0, height, width, 0, rgb::Color(255, 0, 255));
}