inherit "/std/npc/surface_decorator";
void setup() {
    set_name( "worker" );
    set_short( "construction worker" );
    add_property( "determinate", "a " );
    add_adjective( "construction" );
    add_property( "unique", 1 );
    setup_nationality( "/std/nationality/agatean", "Bes Pelargic" );
    basic_setup( "human", "warrior", 30 );
    set_gender( 1 );
    set_long("This is a construction worker.  You can use him to "
        "decorate surfaces in player housing to the exact specifications "
        "that you will set later in this file.  He is slightly grubby, "
        "is covered in dust and paint, and likes to do wolf whistles.\n");
    add_property( "place", "Counterweight Continent" );
    add_allowed_surface( "floor" );
    add_allowed_surface( "wall" );
    add_fitted_surface( "plush green carpet", "covered with plush "
        "green carpet", 1000 );
    add_fitted_surface( "plush red carpet", "covered with plush "
        "red carpet", 1000 );
    add_fitted_surface( "plush yellow carpet", "covered with plush "
        "yellow carpet", 1000 );
    add_fitted_surface( "plush blue carpet", "covered with plush "
        "blue carpet", 1000 );
    set_under_construction_mess( "covered in dust, plaster and carpet bits" );
    add_allowed_domain( "/w/una" );
    add_allowed_domain( "/d/cwc/Bes_Pelargic" );
    set_responses( ({
        "'I don't fit those kinds of surfaces matey!",
        "'I've never heard of those sort of carpets, arrrrr.",
        "'Arr, you don't own this place, mister!",
        "'I can't be decoratin' these here surfaces, shogun!  You should "
        "take me to a house!",
        "'Arr matey, something went horribly wrong!",
        "'Arrrr matey, all done!",
        "'You don't have enough money to pay for the $decor$!  It "
        "will cost you $amount$, guv!",
        "'I can fit $allowed$ with any of the following:",
        "'Cor blimey mister, I haven't got any stock.",
        "'Okey doke, I'll have it done in a jiffy guv'nor!",
        "'What?  Who sed dat?",
        "'I've already got this great job with $employer$, mate!",
        "'Righty-o, you just take me to the room you want spiffied "
        "up and ask me to fit something!",
        "'Sorry matey, bad karma over that way."
    }) );
}