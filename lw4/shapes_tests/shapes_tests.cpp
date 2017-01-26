#include "stdafx.h"

#include "../shapes/IShape.h"
#include "../shapes/ISolidShape.h"
#include "../shapes/Shape.h"
#include "../shapes/SolidShape.h"
#include "../shapes/LineSegment.h"
#include "../shapes/Triangle.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Circle.h"

namespace
{

static const auto eps = 0.001;
static const unsigned PRECISION = 1;

void VerifyPoint(const CPoint & lhs, const CPoint & rhs)
{
	BOOST_CHECK_CLOSE_FRACTION(lhs.x, rhs.x, eps);
	BOOST_CHECK_CLOSE_FRACTION(lhs.y, rhs.y, eps);
}

}

BOOST_AUTO_TEST_SUITE(Line_Segment)

	BOOST_AUTO_TEST_SUITE(has_forming_point)

		BOOST_AUTO_TEST_CASE(begin_point)
		{
			VerifyPoint(CLineSegment({ 0, 0 }, { 0, 0 }, "FFFFFF").GetStartPoint(), { 0, 0 });
			VerifyPoint(CLineSegment({ 4.72, -6.145 }, { -4.51, 4.981 }, "FFFFFF").GetStartPoint(), { 4.72, -6.145 });
		}

		BOOST_AUTO_TEST_CASE(end_point)
		{
			VerifyPoint(CLineSegment({ 0, 0 }, { 0, 0 }, "FFFFFF").GetEndPoint(), { 0, 0 });
			VerifyPoint(CLineSegment({ 4.72, -6.145 }, { -4.51, 4.981 }, "FFFFFF").GetEndPoint(), { -4.51, 4.981 });
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(always_has_zero_area)
	{
		BOOST_CHECK_CLOSE_FRACTION(CLineSegment({ 0, 0 }, { 1, 1 }, "FFFFFF").GetArea(), 0.0, eps);
	}

	BOOST_AUTO_TEST_CASE(has_perimeter)
	{
		BOOST_CHECK_CLOSE_FRACTION(CLineSegment({ 0, 0 }, { 0, 0 }, "FFFFFF").GetPerimeter(), 0.0, eps);
		BOOST_CHECK_CLOSE_FRACTION(CLineSegment({ 0, 0 }, { 0, 1 }, "FFFFFF").GetPerimeter(), 1.0, eps);
		BOOST_CHECK_CLOSE_FRACTION(CLineSegment({ 0, 0 }, { 1, 0 }, "FFFFFF").GetPerimeter(), 1.0, eps);
		BOOST_CHECK_CLOSE_FRACTION(CLineSegment({ 0, 0 }, { -1, -1 }, "FFFFFF").GetPerimeter(), sqrt(2.0), eps);
		BOOST_CHECK_CLOSE_FRACTION(CLineSegment({ 1, 1 }, { -1, -1 }, "FFFFFF").GetPerimeter(), sqrt(8.0), eps);
	}

	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK_EQUAL(CLineSegment({ 0, 0 }, { 0, 0 }, "FFFFFF").GetOutlineColor(), "FFFFFF");
		BOOST_CHECK_EQUAL(CLineSegment({ -4.5, -2 }, { 1.72, 49.57 }, "A0F973").GetOutlineColor(), "A0F973");
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		BOOST_CHECK_EQUAL(CLineSegment({ 0, 0 }, { 0, 0 }, "FFFFFF").ToString(), "line_segment: 0.0 0.0 FFFFFF 0.0 0.0 0.0 0.0\n");
		BOOST_CHECK_EQUAL(CLineSegment({ -4.5, -2 }, { 1.72, 49.57 }, "A0F973").ToString(), "line_segment: 0.0 51.9 A0F973 -4.5 -2.0 1.7 49.6\n");
	}

BOOST_AUTO_TEST_SUITE_END()

/*========================================================================================================================================*/

BOOST_AUTO_TEST_SUITE(Triangle)

	BOOST_AUTO_TEST_SUITE(has_forming_point)

		BOOST_AUTO_TEST_CASE(first_point)
		{
			VerifyPoint(CTriangle({ 0, 0 }, { 0, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF").GetVertex1(), { 0, 0 });
			VerifyPoint(CTriangle({ 4.72, -6.145 }, { -4.51, 4.981 }, { 0.14, -0.173 }, "FFFFFF", "FFFFFF").GetVertex1(), { 4.72, -6.145 });
		}

		BOOST_AUTO_TEST_CASE(second_point)
		{
			VerifyPoint(CTriangle({ 0, 0 }, { 0, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF").GetVertex2(), { 0, 0 });
			VerifyPoint(CTriangle({ 4.72, -6.145 }, { -4.51, 4.981 }, { 0.14, -0.173 }, "FFFFFF", "FFFFFF").GetVertex2(), { -4.51, 4.981 });
		}

		BOOST_AUTO_TEST_CASE(third_point)
		{
			VerifyPoint(CTriangle({ 0, 0 }, { 0, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF").GetVertex3(), { 0, 0 });
			VerifyPoint(CTriangle({ 4.72, -6.145 }, { -4.51, 4.981 }, { 0.14, -0.173 }, "FFFFFF", "FFFFFF").GetVertex3(), { 0.14, -0.173 });
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(has_perimeter)
	{
		BOOST_CHECK_CLOSE_FRACTION(CTriangle({ 0, 3 }, { 4, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF").GetPerimeter(), 12.0, eps);
		BOOST_CHECK_CLOSE_FRACTION(CTriangle({ 5, 0 }, { 0, 12 }, { 0, 13 }, "FFFFFF", "FFFFFF").GetPerimeter(), 13 + sqrt(194) + 1, eps);
		BOOST_CHECK_CLOSE_FRACTION(CTriangle({ 1, 2 }, { 5, 4 }, { 5, 6 }, "FFFFFF", "FFFFFF").GetPerimeter(), 2 + 4 * sqrt(2) + 2 * sqrt(5), eps);
	}

	BOOST_AUTO_TEST_CASE(has_area)
	{
		BOOST_CHECK_CLOSE_FRACTION(CTriangle({ 0, 3 }, { 4, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF").GetArea(), 6.0, eps);
		BOOST_CHECK_CLOSE_FRACTION(CTriangle({ 5, 0 }, { 0, 12 }, { 0, 13 }, "FFFFFF", "FFFFFF").GetArea(), 2.5, eps);
		BOOST_CHECK_CLOSE_FRACTION(CTriangle({ 1, 2 }, { 5, 4 }, { 5, 6 }, "FFFFFF", "FFFFFF").GetArea(), 4, eps);
	}

	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK_EQUAL(CTriangle({ 0, 3 }, { 4, 0 }, { 0, 0 }, "FFFFFF", "A0F973").GetOutlineColor(), "FFFFFF");
		BOOST_CHECK_EQUAL(CTriangle({ -4.5, -2 }, { 1.72, 49.57 }, { 0, 0 }, "A0F973", "FFFFFF").GetOutlineColor(), "A0F973");
	}

	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK_EQUAL(CTriangle({ 0, 3 }, { 4, 0 }, { 0, 0 }, "FFFFFF", "A0F973").GetFillColor(), "A0F973");
		BOOST_CHECK_EQUAL(CTriangle({ -4.5, -2 }, { 1.72, 49.57 }, { 0, 0 }, "A0F973", "FFFFFF").GetFillColor(), "FFFFFF");
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		BOOST_CHECK_EQUAL(CTriangle({ 0, 3 }, { 4, 0 }, { 0, 0 }, "FFFFFF", "A0F973").ToString(),
		                  "triangle: 6.0 12.0 FFFFFF A0F973 0.0 3.0 4.0 0.0 0.0 0.0\n");
		BOOST_CHECK_EQUAL(CTriangle({ -4.5, -2 }, { 1.72, 49.57 }, { -17.2, 14.989 }, "A0F973", "FFFFFF").ToString(),
		                  "triangle: 380.3 112.6 A0F973 FFFFFF -4.5 -2.0 1.7 49.6 -17.2 15.0\n");
	}

BOOST_AUTO_TEST_SUITE_END()

/*=======================================================================================================================================*/

BOOST_AUTO_TEST_SUITE(Rectangle)

	BOOST_AUTO_TEST_CASE(cannot_have_left_vertex_larger_than_right_by_Ox)
	{
		BOOST_REQUIRE_THROW(CRectangle({ 10, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF"), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(cannot_have_left_vertex_more_less_than_right_by_Oy)
	{
		BOOST_REQUIRE_THROW(CRectangle({ 0, 0 }, { 0, 10 }, "FFFFFF", "FFFFFF"), std::invalid_argument);
	}

	BOOST_AUTO_TEST_SUITE(has_forming_point)

		BOOST_AUTO_TEST_CASE(left_top)
		{
			VerifyPoint(CRectangle({ 0, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF").GetLeftTop(), { 0, 0 });
			VerifyPoint(CRectangle({ -4.72, 6.145 }, { -4.51, 4.981 }, "FFFFFF", "FFFFFF").GetLeftTop(), { -4.72, 6.145 });
		}

		BOOST_AUTO_TEST_CASE(right_bottom)
		{
			VerifyPoint(CRectangle({ 0, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF").GetRightBottom(), { 0, 0 });
			VerifyPoint(CRectangle({ -4.72, 6.145 }, { -4.51, 4.981 }, "FFFFFF", "FFFFFF").GetRightBottom(), { -4.51, 4.981 });
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(has_width)
	{
		BOOST_CHECK_CLOSE_FRACTION(CRectangle({ 0, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF").GetWidth(), 0, eps);
		BOOST_CHECK_CLOSE_FRACTION(CRectangle({ -4.72, 6.145 }, { -4.51, 4.981 }, "FFFFFF", "FFFFFF").GetWidth(), 4.72 - 4.51, eps);
	}

	BOOST_AUTO_TEST_CASE(has_height)
	{
		BOOST_CHECK_CLOSE_FRACTION(CRectangle({ 0, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF").GetHeight(), 0, eps);
		BOOST_CHECK_CLOSE_FRACTION(CRectangle({ -4.72, 6.145 }, { -4.51, 4.981 }, "FFFFFF", "FFFFFF").GetHeight(), 6.145 - 4.981, eps);
	}

	BOOST_AUTO_TEST_CASE(has_perimeter)
	{
		BOOST_CHECK_CLOSE_FRACTION(CRectangle({ 0, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF").GetPerimeter(), 0, eps);
		BOOST_CHECK_CLOSE_FRACTION(CRectangle({ -4.72, 6.145 }, { -4.51, 4.981 }, "FFFFFF", "FFFFFF").GetPerimeter(), 2 * (0.21 + 1.164), eps);
	}

	BOOST_AUTO_TEST_CASE(has_area)
	{
		BOOST_CHECK_CLOSE_FRACTION(CRectangle({ 0, 0 }, { 0, 0 }, "FFFFFF", "FFFFFF").GetArea(), 0, eps);
		BOOST_CHECK_CLOSE_FRACTION(CRectangle({ -4.72, 6.145 }, { -4.51, 4.981 }, "FFFFFF", "FFFFFF").GetArea(), 0.24444, eps);
	}

	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK_EQUAL(CRectangle({ 0, 0 }, { 0, 0 }, "FFFFFF", "A0F973").GetOutlineColor(), "FFFFFF");
		BOOST_CHECK_EQUAL(CRectangle({ -4.72, 6.145 }, { -4.51, 4.981 }, "A0F973", "FFFFFF").GetOutlineColor(), "A0F973");
	}

	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK_EQUAL(CRectangle({ 0, 0 }, { 0, 0 }, "FFFFFF", "A0F973").GetFillColor(), "A0F973");
		BOOST_CHECK_EQUAL(CRectangle({ -4.72, 6.145 }, { -4.51, 4.981 }, "A0F973", "FFFFFF").GetFillColor(), "FFFFFF");
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		BOOST_CHECK_EQUAL(CRectangle({ 3, 0 }, { 4, -2 }, "FFFFFF", "A0F973").ToString(),
		                  "rectangle: 2.0 6.0 FFFFFF A0F973 3.0 0.0 4.0 -2.0\n");
		BOOST_CHECK_EQUAL(CRectangle({ -4.5, 49.57 }, { 1.72, -2 }, "A0F973", "FFFFFF").ToString(),
		                  "rectangle: 320.8 115.6 A0F973 FFFFFF -4.5 49.6 1.7 -2.0\n");
	}

BOOST_AUTO_TEST_SUITE_END()

/*=======================================================================================================================================*/

BOOST_AUTO_TEST_SUITE(Circle)

	BOOST_AUTO_TEST_CASE(cannot_be_not_positive)
	{
		BOOST_REQUIRE_THROW(CCircle({ 0, 0 }, -1, "FFFFFF", "FFFFFF"), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(has_center)
	{
		VerifyPoint(CCircle({ 0, 0 }, 0, "FFFFFF", "FFFFFF").GetCenter(), { 0, 0 });
		VerifyPoint(CCircle({ -4.72, 6.145 }, 5.7, "FFFFFF", "FFFFFF").GetCenter(), { -4.72, 6.145 });
	}

	BOOST_AUTO_TEST_CASE(has_radius)
	{
		BOOST_CHECK_EQUAL(CCircle({ 0, 0 }, 0, "FFFFFF", "FFFFFF").GetRadius(), 0);
		BOOST_CHECK_EQUAL(CCircle({ -4.72, 6.145 }, 5.7, "FFFFFF", "FFFFFF").GetRadius(), 5.7);
	}

	BOOST_AUTO_TEST_CASE(has_perimeter)
	{
		BOOST_CHECK_CLOSE_FRACTION(CCircle({ 0, 0 }, 0, "FFFFFF", "FFFFFF").GetPerimeter(), 0, eps);
		BOOST_CHECK_CLOSE_FRACTION(CCircle({ -4.72, 6.145 }, 5.7, "FFFFFF", "FFFFFF").GetPerimeter(), 35.814, eps);
	}

	BOOST_AUTO_TEST_CASE(has_area)
	{
		BOOST_CHECK_CLOSE_FRACTION(CCircle({ 0, 0 }, 0, "FFFFFF", "FFFFFF").GetArea(), 0, eps);
		BOOST_CHECK_CLOSE_FRACTION(CCircle({ -4.72, 6.145 }, 5.7, "FFFFFF", "FFFFFF").GetArea(), 102.070, eps);
	}

	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK_EQUAL(CCircle({ 0, 0 }, 0, "FFFFFF", "A0F973").GetOutlineColor(), "FFFFFF");
		BOOST_CHECK_EQUAL(CCircle({ -4.72, 6.145 }, 5.7, "A0F973", "FFFFFF").GetOutlineColor(), "A0F973");
	}

	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK_EQUAL(CCircle({ 0, 0 }, 0, "FFFFFF", "A0F973").GetFillColor(), "A0F973");
		BOOST_CHECK_EQUAL(CCircle({ -4.72, 6.145 }, 5.7, "A0F973", "FFFFFF").GetFillColor(), "FFFFFF");
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		BOOST_CHECK_EQUAL(CCircle({ 3, 0 }, 4, "FFFFFF", "A0F973").ToString(),
			"circle: 50.3 25.1 FFFFFF A0F973 3.0 0.0 4.0\n");
		BOOST_CHECK_EQUAL(CCircle({ -4.5, 49.57 }, 0.763, "A0F973", "FFFFFF").ToString(),
			"circle: 1.8 4.8 A0F973 FFFFFF -4.5 49.6 0.8\n");
	}

BOOST_AUTO_TEST_SUITE_END()
