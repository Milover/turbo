auto& control
{
	geometry::interface::GmshControl::initialize(output, output)
};

geometry::Model model {};

auto updateAndWait = [&](const double time) -> void
{
	geometry::interface::GmshBase::synchronize();
	control.update();
	test::pause(time, output);
};
