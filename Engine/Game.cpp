/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <complex>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	camera(-3.0f, -2.0f)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed('W'))
	{
		camera.y -= cameraSpeed;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		camera.y += cameraSpeed;
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		camera.x -= cameraSpeed;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		camera.x += cameraSpeed;
	}

	if (wnd.kbd.KeyIsPressed('Q'))
	{
		zoom -= 0.25f;
		if (zoom <= 0.0f)
		{
			zoom = 1.0f;
		}
	}
	if (wnd.kbd.KeyIsPressed('E'))
	{
		zoom += 0.25f;
	}
}

constexpr int Game::GetDim()
{
	return Graphics::ScreenWidth/resolution;
}

Color Game::getC(float time)
{
	float hue = std::fmod(time, 360.0f);

	// Convert hue to RGB
	float c = 1.0f;
	float x = c * (1 - float(std::abs(std::fmod(hue / 60.0, 2)) - 1));
	float m = 0.0f;

	float r, g, b;
	if (hue >= 0 && hue < 60) {
		r = c;
		g = x;
		b = 0;
	}
	else if (hue >= 60 && hue < 120) {
		r = x;
		g = c;
		b = 0;
	}
	else if (hue >= 120 && hue < 180) {
		r = 0;
		g = c;
		b = x;
	}
	else if (hue >= 180 && hue < 240) {
		r = 0;
		g = x;
		b = c;
	}
	else if (hue >= 240 && hue < 300) {
		r = x;
		g = 0;
		b = c;
	}
	else {
		r = c;
		g = 0;
		b = x;
	}

	return Color(unsigned char(255* r), unsigned char(255*g), unsigned char(255*b));
}

void Game::ComposeFrame()
{
	double resolutionStep = float((1 - (-3))) / float(Dim);

	for (int j = 0; j < Dim; j++)
	{
		for (int i = 0; i < Dim; i++)
		{
			//Logic
			//Get the coordonates of the pixel in respect to the resolution
			//I want the most left side to be -2 and the most right side to be +1 since it will fit better in the screen
			Color color(Colors::Black);
			std::complex<double> c((double(camera.x) + resolutionStep * double(i)) / zoom, 
									(double(camera.y) + resolutionStep * double(j)) / zoom);

			//Mandelbrot function applied to the complex number z = x + iy
			std::complex<double> zn(0.0, 0.0);
			for (int it = 0; it < maxIteration; it++)
			{
				zn = zn * zn + c;
				if (float(std::norm(zn)) > normTreshold)
				{
					color = getC(float(it));
					break;
				}
			}



			//Drawing
			for (int m = 0; m < resolution; m++)
			{
				for (int n = 0; n < resolution; n++)
				{
					gfx.PutPixel(m + i * resolution, n + j * resolution, color);
				}
			}
		}
	}
}
