auto& control
{
	interface::GmshControl::initialize(output, output)
};

geometry::Model model {};

auto updateAndWait = [&](const double time) -> void
{
	interface::GmshBase::synchronize();
	control.update();
	test::pause(time, output);
};
