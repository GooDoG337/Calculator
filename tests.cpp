#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calculate.h"

std::string expression; //I've been a fool...
TEST_SUITE("Simple math") {
    TEST_SUITE("Just plus") {
        TEST_CASE("2+3") {
            expression = "2+3";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(5).epsilon(0.01));
        }
        TEST_CASE("-5+30") {
            expression = "-5+30";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(25).epsilon(0.01));
        }
        TEST_CASE("43+-17") {
            expression = "43--17";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(60).epsilon(0.01));
        }
        TEST_CASE("-76+-17") {
            expression = "-76+-17";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(-93).epsilon(0.01));
        }
    }
    TEST_SUITE("Just minus") {
        TEST_CASE("2-3") {
            expression = "2-3";
            Calculate(expression);
            CHECK_EQ(stod(expression), -1);
        }
        TEST_CASE("5-2") {
            expression = "-5-2";
            Calculate(expression);
            CHECK_EQ(stod(expression), -7);
        }
        TEST_CASE("-5--5") {
            expression = "-5--5";
            Calculate(expression);
            CHECK_EQ(stod(expression), 0);
        }
        TEST_CASE("-7-7") {
            expression = "-7-7";
            Calculate(expression);
            CHECK_EQ(stod(expression), -14);
        }
    }
    TEST_SUITE("Just multiplication") {
        TEST_CASE("2*3") {
            expression = "2*3";
            Calculate(expression);
            CHECK_EQ(stod(expression), 6);
        }
        TEST_CASE("7*-5") {
            expression = "7*-5";
            Calculate(expression);
            CHECK_EQ(stod(expression), -35);
        }
        TEST_CASE("-6*-3") {
            expression = "-6*-3";
            Calculate(expression);
            CHECK_EQ(stod(expression), 18);
        }
        TEST_CASE("-3*8") {
            expression = "-3*8";
            Calculate(expression);
            CHECK_EQ(stod(expression), -24);
        }
    }
    TEST_SUITE("Just division") {
        TEST_CASE("2/7") {
            expression = "2/7";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(2.0/7.0).epsilon(0.01));
        }
        TEST_CASE("75/-5") {
            expression = "75/-5";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(75.0/-5.0).epsilon(0.01));
        }
        TEST_CASE("-66/11") {
            expression = "-66/11";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(-66.0/11.0).epsilon(0.01));
        }
        TEST_CASE("-54/-9") {
            expression = "-54/-9";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(-54.0/-9.0).epsilon(0.01));
        }
    }
}

TEST_SUITE("sus math") {
    TEST_SUITE("Spaces between signs") {
        TEST_CASE("2  +  3") {
            expression = "2  +  3";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(5).epsilon(0.01));
        }
        TEST_CASE("-6*-    3") {
            expression = "-6*-    3";
            Calculate(expression);
            CHECK_EQ(stod(expression), 18);
        }
        TEST_CASE("-    54/    -9") {
            expression = "-    54/    -9";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(-54.0/-9.0).epsilon(0.01));
        }
    }

    TEST_SUITE("Space = multiplication. Wolfram?") {
            TEST_CASE("2 3") {
                expression = "2 3";
                Calculate(expression);
                CHECK_EQ(stod(expression), 6);
            }
            TEST_CASE("-3 8") {
                expression = "-3*8";
                Calculate(expression);
                CHECK_EQ(stod(expression), -24);
            }
        }

    TEST_SUITE("Not fully entered number") {
        TEST_CASE("6./7") {
            expression = "6./7";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(6.0/7.0).epsilon(0.01));
        }
        TEST_CASE("10./50.") {
            expression = "10./50.";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(10.0/50.0).epsilon(0.01));
        }
        TEST_CASE(".45/.5") {
            expression = ".45/.5";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(0.45/0.5).epsilon(0.01));
        }
        TEST_CASE("7./.5") {
            expression = "7./.5";
            Calculate(expression);
            CHECK_EQ(stod(expression), doctest::Approx(7.0/0.5).epsilon(0.01));
        }
    }
    }

TEST_SUITE("Complex math") {
    TEST_CASE("104/62*76-53+22") {
        expression = "104/62*76-53+22";
        Calculate(expression);
        CHECK_EQ(stod(expression), doctest::Approx(104.0/(62*76)-53+22).epsilon(0.01));
    }
    TEST_CASE("1-54*12+65-44*11") {
        expression = "1-54*12+65-44*11";
        Calculate(expression);
        CHECK_EQ(stod(expression), doctest::Approx(1-54*12+65-44*11).epsilon(0.01));
    }
    TEST_CASE("54/32*76-54/44*2") {
        expression = "54/32*76-54/44*2";
        Calculate(expression);
        CHECK_EQ(stod(expression), doctest::Approx(54.0/(32*76)-54.0/(44*2)).epsilon(0.01));
    }
    TEST_CASE("2*3*4*5/33+55-111") {
        expression = "2*3*4*5/33+55-111";
        Calculate(expression);
        CHECK_EQ(stod(expression), doctest::Approx((2*3*4*5)/33.0+55-111).epsilon(0.01));
    }
}

TEST_SUITE("Exceptions test") {
    TEST_CASE("444/0") {
        expression = "444/0";
        CHECK_THROWS(Calculate(expression));
        //CHECK_THROWS_WITH(Calculate(expression), doctest::Contains("деление"));
    }
    TEST_CASE("444/a") {
        expression = "444/a";
        CHECK_THROWS(Calculate(expression));
       //CHECK_THROWS_WITH(Calculate(expression), doctest::Contains("символ"));
    }
    TEST_CASE(".t/77") {
        expression = ".t/77";
        CHECK_THROWS(Calculate(expression));
        //CHECK_THROWS_WITH(Calculate(expression), doctest::Contains("символ"));
    }
    TEST_CASE("65*********5") {
        expression = "65*********5";
        CHECK_THROWS(Calculate(expression));
    }
    TEST_CASE("655*") {
        expression = "655*";
        CHECK_THROWS(Calculate(expression));
    }
    TEST_CASE("+54") {
        expression = "+54";
        CHECK_THROWS(Calculate(expression));
    }
    TEST_CASE(".555.5+3") {
        expression = ".555.5+3";
        CHECK_THROWS(Calculate(expression));
    }
}