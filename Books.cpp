#include "Books.h"
#include "Animation.h"
#include "Controller.h"


using namespace std;

	string Book::get_title()
	{
		return title;
	}

	void Book::set_id(int i)
	{
		id = i;
	}

	float Book::get_price()
	{
		return price;
	}

	///Returns id with incrementing
	int Book::get_id()
	{
		string file = "Update ID.txt";

		ifstream last_id;
		last_id.open(file.c_str());
		last_id >> id;
		last_id.close();

		ofstream update_id;
		update_id.open(file.c_str());
		update_id << (id + 1);
		update_id.close();

		return id;
	}

	///Returns id whithout incrementing
	int Book::get_id_no_update()
	{
		return id;
	}

	float Book::get_rating()
	{
		return rating;
	}

	string Book::get_release_date()
	{
		return release_date;
	}

	string Book::get_language()
	{
		return language;
	}

	string Book::get_edition()
	{
		return edition;
	}

	string Book::get_genre()
	{
		return genre;
	}

	string Book::get_writer()
	{
		return writer;
	}

	void Book::set_title()
	{
		string t;
		getline(cin, t);
		title = t;
	}

	void Book::set_price()
	{
		float t = -1;
		while (t < 0 || !(cin.good()) || t > 10000000)
		{
				cin.clear();
				cin.ignore(100, '\n');
				Animation::colorize_text("\t\t\t\t    Price: ", 14);
				cin >> t;
				price = t;
		}
	}

	void Book::set_release_date()
	{
		string t;
		getline(cin, t);
		release_date = t;
	}

	void Book::set_language()
	{
		string t;
		Animation::colorize_text("\t\t\t\t    Language: ", 14);
		cin >> t;
		language = t;
	}

	void Book::set_edition()
	{
		string t;
		getline(cin, t);
		edition = t;
	}

	void Book::set_writer()
	{
		string t;
		getline(cin, t);
		writer = t;
	}

	void Book::set_rating()
	{
		float t = - 1;
		while (t < 1 || t > 10 || !(cin.good()))
		{
			cin.clear();
			cin.ignore(100, '\n');
			Animation::colorize_text("\t\t\t\t    Rating (1 -> 10): ", 14);
			cin >> t;
			rating = t;
		}

	}

	void Book::set_genre()
	{
		string t;
		getline(cin, t);
		genre = t;
	}


	///Paper_book functions
	string Paper_book::get_publisher()
	{
		return  publisher;
	}

	int Paper_book::get_pages()
	{
		return pages;
	}

	void Paper_book::set_publisher()
	{
		Animation::colorize_text("\t\t\t\t    Publisher: ", 14);
		cin >> publisher;
	}

	void Paper_book::set_pages()
	{
		int t = -1;
		while (t < 0 || !(cin.good()))
		{
			cin.clear();
			cin.ignore(100, '\n');
			Animation::colorize_text("\t\t\t\t    Volume in pages: ", 14);
			cin >> t;
			pages = t;
		}
	}

	///Audio_cd functions
	string Audio_cd::get_listening_length()
	{
		return  listening_length;
	}

	string Audio_cd::get_voice()
	{
		return  voice;
	}

	void Audio_cd::set_voice()
	{
		cin.ignore(100, '\n');
		getline(cin, voice);
	}

	void Audio_cd::set_listening_length()
	{
		getline(cin, listening_length);
	}

    ///Implementation of pure virtual function by derived classes
	void Paper_book::add_book()
	{
		system("cls");
		Paper_book pb;
		int color_yellow = 14;
		int color = 10;
		cout << endl;

		Animation::draw_border(61, color);
		Animation::colorize_text("\t\t\t\t                  Fill the form to add book         \n", 07);
		Animation::draw_border(61, color);
		cout << endl;
		Animation::colorize_text("\n\t\t\t\t    Title: ", color_yellow);
		pb.set_title();
		Animation::colorize_text("\t\t\t\t    Release date: ", color_yellow);
		pb.set_release_date();
		Animation::colorize_text("\t\t\t\t    Author: ", color_yellow);
		pb.set_writer();
		Animation::colorize_text("\t\t\t\t    genre: ", color_yellow);
		pb.set_genre();
		Animation::colorize_text("\t\t\t\t    Edition: ", color_yellow);
		pb.set_edition();
		pb.set_language();
		pb.set_rating();
		pb.set_price();
		pb.set_publisher();
		pb.set_pages();
		Animation::colorize_text("\t\t\t\t    ID of this book in the system: ", 3);
		cout << pb.get_id();
		cout << endl;
		cout << endl;
		ofstream pb_write;
		pb_write.open("DataBase/Paper Books/book - " + to_string(pb.get_id_no_update()) + ".info");
		pb_write << pb.get_id_no_update() << endl;
		pb_write << pb.get_title() << endl;
		pb_write << pb.get_release_date() << endl;
		pb_write << pb.get_writer() << endl;
		pb_write << pb.get_genre() << endl;
		pb_write << pb.get_edition() << endl;
		pb_write << pb.get_language() << endl;
		pb_write << pb.get_rating() << endl;
		pb_write << pb.get_price() << endl;
		pb_write << pb.get_publisher() << endl;
		pb_write << pb.get_pages() << endl;
		pb_write.close();

		Animation::draw_border(61, color);
		Animation::frame_phrase("                                                         ", color);
		Animation::frame_phrase(" New paper book has been successfully added to database  ", color);
		Animation::frame_phrase("                                                         ", color);
		Animation::frame_phrase("             -> Press any key to go back <-              ", color);
		Animation::frame_phrase("                                                         ", color);
		Animation::draw_border(61, color);
		cout << endl;

        getch();
        system("cls");
        Controller c;
        c.control_panel();
	};

	void Audio_cd::add_book()
	{
		system("cls");
		Audio_cd pb;
		int color_yellow = 14;
		int color = 10;
		cout << endl;
		Animation::draw_border(61, color);
		Animation::colorize_text("\t\t\t\t                  Fill the form to add book         \n", 07);
		Animation::draw_border(61, color);
		cout << endl;
		Animation::colorize_text("\t\t\t\t    Title: ", color_yellow);
		pb.set_title();
		Animation::colorize_text("\t\t\t\t    Release date: ", color_yellow);
		pb.set_release_date();
		Animation::colorize_text("\t\t\t\t    Author: ", color_yellow);
		pb.set_writer();
		Animation::colorize_text("\t\t\t\t    genre: ", color_yellow);
		pb.set_genre();
		Animation::colorize_text("\t\t\t\t    Edition: ", color_yellow);
		pb.set_edition();
		pb.set_language();
		pb.set_rating();
		pb.set_price();
		Animation::colorize_text("\t\t\t\t    Voice: ", color_yellow);
		pb.set_voice();
		Animation::colorize_text("\t\t\t\t    Listening length (hours): ", color_yellow);
		pb.set_listening_length();
		Animation::colorize_text("\t\t\t\t    ID of this book in the system: ", 3);
		cout << pb.get_id();
		cout << endl;
		cout << endl;
		Animation::draw_border(61, color);
		Animation::frame_phrase("                                                         ", color);
		Animation::frame_phrase(" New audio book has been successfully added to database  ", color);
		Animation::frame_phrase("                                                         ", color);
		Animation::frame_phrase("             -> Press any key to go back <-              ", color);
		Animation::frame_phrase("                                                         ", color);
		Animation::draw_border(61, color);
		cout << endl;

		ofstream pb_write;
		pb_write.open("DataBase/Audio CD/book - " + to_string(pb.get_id_no_update()) + ".info");
		pb_write << pb.get_id_no_update() << endl;
		pb_write << pb.get_title() << endl;
		pb_write << pb.get_release_date() << endl;
		pb_write << pb.get_writer() << endl;
		pb_write << pb.get_genre() << endl;
		pb_write << pb.get_edition() << endl;
		pb_write << pb.get_language() << endl;
		pb_write << pb.get_rating() << endl;
		pb_write << pb.get_price() << endl;
		pb_write << pb.get_voice() << endl;
		pb_write << pb.get_listening_length() << endl;
		pb_write.close();

        getch();
		system("cls");
        Controller c;
        c.control_panel();
	};

	void Digital_book::add_book()
	{
		system("cls");
		Digital_book pb;
		int color_yellow = 14;
		int color = 10;
		cout << endl;
		Animation::draw_border(61, color);
		Animation::colorize_text("\t\t\t\t                  Fill the form to add book         \n", 07);
		Animation::draw_border(61, color);
		cout << endl;
		Animation::colorize_text("\t\t\t\t    Title: ", color_yellow);
		pb.set_title();
		Animation::colorize_text("\t\t\t\t    Release date: ", color_yellow);
		pb.set_release_date();
		Animation::colorize_text("\t\t\t\t    Author: ", color_yellow);
		pb.set_writer();
		Animation::colorize_text("\t\t\t\t    genre: ", color_yellow);
		pb.set_genre();
		Animation::colorize_text("\t\t\t\t    Edition: ", color_yellow);
		pb.set_edition();
		pb.set_language();
		pb.set_rating();
		pb.set_price();
		Animation::colorize_text("\t\t\t\t    ID of this book in the system: ", 3);
		cout << pb.get_id();
		cout << endl;
		cout << endl;
		Animation::draw_border(61, color);
		Animation::frame_phrase("                                                         ", color);
		Animation::frame_phrase(" New Digital book has been successfully added to database  ", color);
		Animation::frame_phrase("                                                         ", color);
		Animation::frame_phrase("             -> Press any key to go back <-              ", color);
		Animation::frame_phrase("                                                         ", color);
		Animation::draw_border(61, color);
		cout << endl;

		ofstream pb_write;
		pb_write.open("DataBase/Digital Books/book - " + to_string(pb.get_id_no_update()) + ".info");
		pb_write << pb.get_id_no_update() << endl;
		pb_write << pb.get_title() << endl;
		pb_write << pb.get_release_date() << endl;
		pb_write << pb.get_writer() << endl;
		pb_write << pb.get_genre() << endl;
		pb_write << pb.get_edition() << endl;
		pb_write << pb.get_language() << endl;
		pb_write << pb.get_rating() << endl;
		pb_write << pb.get_price() << endl;
		pb_write.close();

        getch();
        system("cls");
		Controller c;
		c.control_panel();
	};
