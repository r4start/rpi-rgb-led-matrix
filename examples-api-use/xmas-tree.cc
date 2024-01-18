#include <atomic>
#include <memory>
#include <thread>

#include <signal.h>

#include <led-matrix.h>

namespace rgb = rgb_matrix;

static auto create_options() -> rgb::RGBMatrix::Options;
static void draw(rgb::Canvas *c, std::atomic_bool &flag);

static std::atomic_bool STOP_FLAG = false;
static void interrupt(int signo);

static constexpr rgb::Color WHITE = rgb::Color(255, 255, 255);
static constexpr rgb::Color BROWN = rgb::Color(165, 42, 42);
static constexpr auto GREEN = rgb::Color(0, 255, 0);

int main() {
  const auto options = create_options();

  auto rt_options = rgb::RuntimeOptions();
  rt_options.gpio_slowdown = 5;

  auto matrix = std::unique_ptr<rgb::RGBMatrix>(
      rgb::CreateMatrixFromOptions(options, rt_options));

  signal(SIGTERM, interrupt);
  signal(SIGINT, interrupt);

  draw(matrix.get(), STOP_FLAG);

  return 0;
}

static auto create_options() -> rgb::RGBMatrix::Options {
  auto options = rgb::RGBMatrix::Options();
  options.cols = 96;
  options.rows = 48;

  options.pwm_lsb_nanoseconds = 130;
  options.pwm_bits = 11;

  options.brightness = 50;

  options.disable_hardware_pulsing = true;

  return options;
}

static void draw(rgb::Canvas *c, std::atomic_bool &flag) {
  using namespace std::chrono_literals;

  constexpr int snow_height = 10;

  const int width = c->width() - 1;
  const int height = c->height() - 1;

  for (;!flag.load(std::memory_order_relaxed);) {
    //rgb::DrawCircle(c, width / 2, height / 2, 10, WHITE);

    // Draw snow on the ground.
    for (int i = 0; i < snow_height; ++i) {
      auto y = height - i;
      rgb::DrawLine(c, 0, y, width, y, WHITE);
    }

    // Draw a tree.
    {
      constexpr auto x = 12;
      constexpr auto tree_width = 3;
      constexpr auto tree_height = 12;
      constexpr auto tree_start_offset = 4;

      // Draw a trunk.
      for (int i = 0; i < tree_height; ++i) {
        auto y = height - tree_start_offset - i;
        rgb::DrawLine(c, x, y, x + tree_width, y, BROWN);
      }

      constexpr auto levels = 5;
      constexpr auto tree_segments_count = 3;

      auto y = height - tree_height - tree_start_offset;

      // Draw main segments.
      for (int segment = 0; segment < tree_segments_count; ++segment) {
        for (int i = levels; i >= 0; --i, --y) {
          rgb::DrawLine(c, x - i, y, x + i + tree_width, y, GREEN);
        }
      }

      // Draw the top
      rgb::DrawLine(c, x + 1, y, x + tree_width - 1, y, GREEN);
    }

    std::this_thread::sleep_for(100ms);
  }
}

static void interrupt(int /*signo*/) {
  STOP_FLAG.store(true, std::memory_order_relaxed);
}