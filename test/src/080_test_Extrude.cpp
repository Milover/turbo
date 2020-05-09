/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing the Extrude class.

\*---------------------------------------------------------------------------*/

#include <utility>
#include <type_traits>

#include "Curve.h"
#include "GmshControl.h"
#include "Extrude.h"
#include "Model.h"
#include "Point.h"
#include "Surface.h"
#include "Vector.h"
#include "Volume.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

geometry::operators::Extrude extruder {};

Vector d_1 {1.0, 0.0};
Vector d_2 {0.0, 1.0};
Vector d_3 {0.0, 0.0, 1.0};


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template
<
	typename Update,
	typename DimensionCheck,
	typename EntityCheck,
	typename EntityCountCheck
>
void testRaw
(
	Update&& updater,
	DimensionCheck&& dc,
	EntityCheck&& ec,
	EntityCountCheck&& ecc
)
{
	auto volume
	{
		extruder
		(
			extruder
			(
				extruder
				(
					geometry::Point::origin(),
					d_1
				),
				d_2
			),
			d_3
		)
	};

	updater(1);
	dc(volume, 3);
	ec(27);	// 8 points, 12 curves, 6 surfaces, 1 volume

	ecc
	(
		8,		// points
		12,		// curves
		6,		// surfaces
		1		// volumes
	);
}


template
<
	typename Update,
	typename DimensionCheck,
	typename EntityCheck,
	typename EntityCountCheck
>
void testRawRvalueRef
(
	Update&& updater,
	DimensionCheck&& dc,
	EntityCheck&& ec,
	EntityCountCheck&& ecc
)
{
	geometry::Point point {geometry::Point::origin()};

	auto curve
	{
		extruder(std::move(point), d_1)
	};

	updater(1);
	dc(curve, 1);
	ec(3);	// 2 points, 1 curve

	auto surface
	{
		extruder(std::move(curve), d_2)
	};

	updater(1);
	dc(surface, 2);
	ec(9);	// 4 points, 4 curves, 1 surface

	auto volume
	{
		extruder(std::move(surface), d_3)
	};

	updater(1);
	dc(volume, 3);
	ec(27);	// 8 points, 12 curves, 6 surfaces, 1 volume

	// we've run 2 tests, so the counts are doubled
	ecc
	(
		16,		// points
		24,		// curves
		12,		// surfaces
		1		// volumes			// FIXME: why 1?
	);
}


template
<
	typename Update,
	typename DimensionCheck,
	typename EntityCheck,
	typename EntityCountCheck
>
void testSptr
(
	Update&& updater,
	DimensionCheck&& dc,
	EntityCheck&& ec,
	EntityCountCheck&& ecc
)
{
	using namespace geometry;

	auto volume
	{
		extruder
		(
			Sptr<Surface>
			{
				new Surface
				{
					extruder
					(
						Sptr<Curve>
						{
							new Curve
							{
								extruder
								(
									Sptr<Point> {new Point {Point::origin()}},
									d_1
								)
							}
						},
						d_2
					)
				}
			},
			d_3
		)
	};

	updater(1);
	dc(volume, 3);
	ec(27);	// 8 points, 12 curves, 6 surfaces, 1 volume

	// we've run 3 tests, so the counts are tripled
	ecc
	(
		24,		// points
		36,		// curves
		18,		// surfaces
		1		// volumes			// FIXME: why 1?
	);
}


template
<
	typename Update,
	typename DimensionCheck,
	typename EntityCheck,
	typename EntityCountCheck
>
void testSptrLvalueRef
(
	Update&& updater,
	DimensionCheck&& dc,
	EntityCheck&& ec,
	EntityCountCheck&& ecc
)
{
	using namespace geometry;

	Sptr<Point> point {new Point {Point::origin()}};

	Sptr<Curve> curve
	{
		new Curve
		{
			extruder(point, d_1)
		}
	};

	updater(1);
	dc(curve, 1);
	ec(3);	// 2 points, 1 curve

	Sptr<Surface> surface
	{
		new Surface
		{
			extruder(curve, d_2)
		}
	};

	updater(1);
	dc(surface, 2);
	ec(9);	// 4 points, 4 curves, 1 surface

	Sptr<Volume> volume
	{
		new Volume
		{
			extruder(surface, d_3)
		}
	};

	updater(1);
	dc(volume, 3);
	ec(27);	// 8 points, 12 curves, 6 surfaces, 1 volume

	// we've run 4 tests, so the counts are quadrupled
	ecc
	(
		32,		// points
		48,		// curves
		24,		// surfaces
		1		// volumes			// FIXME: why 1?
	);
}


template
<
	typename Update,
	typename DimensionCheck,
	typename EntityCheck,
	typename EntityCountCheck
>
void testSptrRvalueRef
(
	Update&& updater,
	DimensionCheck&& dc,
	EntityCheck&& ec,
	EntityCountCheck&& ecc
)
{
	using namespace geometry;

	Sptr<Point> point {new Point {Point::origin()}};

	Sptr<Curve> curve
	{
		new Curve
		{
			extruder(std::move(point), d_1)
		}
	};

	updater(1);
	dc(curve, 1);
	ec(3);	// 2 points, 1 curve

	Sptr<Surface> surface
	{
		new Surface
		{
			extruder(std::move(curve), d_2)
		}
	};

	updater(1);
	dc(surface, 2);
	ec(9);	// 4 points, 4 curves, 1 surface

	Sptr<Volume> volume
	{
		new Volume
		{
			extruder(std::move(surface), d_3)
		}
	};

	updater(1);
	dc(volume, 3);
	ec(27);	// 8 points, 12 curves, 6 surfaces, 1 volume

	// we've run 5 tests, so the counts are quintupled
	ecc
	(
		40,		// points
		60,		// curves
		30,		// surfaces
		1		// volumes			// FIXME: why 1?
	);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	#include "TestInclude.h"
	#include "TestGmshInclude.h"

	auto checkDimension = [&]
	(
		auto&& geometry,
		auto dimension
	) -> void
	{
		if constexpr (isSptr_v<decltype(geometry)>)
		{
			test::compareTest
			(
				pass,
				(geometry->dim == dimension),
				output,
				"Checking dimensions"
			);
		}
		else
			test::compareTest
			(
				pass,
				(geometry.dim == dimension),
				output,
				"Checking dimensions"
			);
	};

	auto checkEntities = [&](auto noEntities) -> void
	{
		test::compareTest
		(
			pass,
			(noEntities = test::getNumberOfEntities()),
			output,
			"Checking number of entities"
		);
	};

	auto checkEntityCount = [&]
	(
		decltype(geometry::Point::count()) noPoints,
		decltype(geometry::Curve::count()) noCurves,
		decltype(geometry::Surface::count()) noSurfaces,
		decltype(geometry::Volume::count()) noVolumes
	) -> void
	{
		test::compareTest
		(
			pass,
			(
				noPoints == geometry::Point::count()
			 && noCurves == geometry::Curve::count()
			 && noSurfaces == geometry::Surface::count()
			 && noVolumes == geometry::Volume::count()
			),
			output,
			"Checking total number of created entities"
		);
	};

	// run the tests
	if (output)
		test::echo("\nRunning raw test\n");
	testRaw
	(
		updateAndWait,
		checkDimension,
		checkEntities,
		checkEntityCount
	);

	if (output)
		test::echo("\nRunning raw rvalue ref test\n");
	testRawRvalueRef
	(
		updateAndWait,
		checkDimension,
		checkEntities,
		checkEntityCount
	);

	if (output)
		test::echo("\nRunning sptr test\n");
	testSptr
	(
		updateAndWait,
		checkDimension,
		checkEntities,
		checkEntityCount
	);

	if (output)
		test::echo("\nRunning sptr lvalue ref test\n");
	testSptrLvalueRef
	(
		updateAndWait,
		checkDimension,
		checkEntities,
		checkEntityCount
	);

	if (output)
		test::echo("\nRunning sptr rvalue ref test\n");
	testSptrRvalueRef
	(
		updateAndWait,
		checkDimension,
		checkEntities,
		checkEntityCount
	);

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);

	control.update();
	control.run();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
