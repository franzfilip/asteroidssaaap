#pragma once
#include <ml5/ml5.h>
#include "spaceship.h"

struct draw_app final : ml5::application
{
	std::unique_ptr<ml5::window> make_window() const override
	{
		return std::make_unique<draw_win>();
	}

private:
	struct draw_win final : ml5::window
	{
		draw_win() : ml5::window{ "ML5.Draw" } {}

	private:
		void on_init() override
		{
			this->get_frame().SetSize(width, height);
			set_prop_background_brush(*wxBLACK_BRUSH);

			start_timer(ml5::duration_t(100000));
		}

		void on_key(ml5::key_event const& event) override {
			std::cout << event.get_key_code() << std::endl;
			switch (event.get_key_code()) {
				case 314: {
					degree = degree + 20;
					spaceshipRenderImg = spaceship.rotateImage(getRad());
					//refresh();
					break;
				}
				case 315: {
					spaceship.increaseSpeed(3);
					spaceship.move(getRad());
					//refresh();
					break;
				}
				case 316: {
					degree = degree - 20;
					spaceshipRenderImg = spaceship.rotateImage(getRad());
					//refresh();
					break;
				}
				case 317: {
					spaceship.reduceSpeed(3);
					//refresh();
					break;
				}
				case 32: {
					spaceship.shoot(getRad());
					//refresh();
					break;
				}
			}
		}

		void on_paint(const ml5::paint_event& event) override
		{
			auto& context{ event.get_context() };

			//Draw Ship
			wxPoint p(spaceship.getCenter().x - spaceshipRenderImg.GetWidth() / 2, spaceship.getCenter().y - spaceshipRenderImg.GetHeight() / 2);
			context.DrawBitmap(spaceshipRenderImg, p);

			//Draw shots
			for(auto shot : spaceship.getShots())
			{
				wxRect r = shot.getBoundingBox();
				context.DrawRectangle(r);
			}
		}

		//void on_mouse_left_down(const ml5::mouse_event& event) override {
			//const auto pos{ event.get_position() };
			//refresh();
		//}

		double getRad() const
		{
			const double pi = 3.1415926535;
			return degree * (pi / 180.0);
		}

		void on_timer(ml5::timer_event const& event) override {
			spaceship.move(getRad());
			spaceship.moveShots();
			//std::cout << "ON_TIMER" << std::endl;
			refresh();
		}

		wxBrush brush{ *wxBLACK_BRUSH };
		wxPen pen{ *wxBLACK_PEN };
		spaceship spaceship{ wxPoint(300, 300), 100 };
		wxImage spaceshipRenderImg{spaceship.getImage()};
		double degree = 0;
		const int width = 1700;
		const int height = 900;
	};
};
