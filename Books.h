#ifndef BOOKS_H
#define BOOKS_H

#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Book
{
protected:
	///variables for all books types
	string title;
	float price;
	int id;
	string release_date;
	string genre;
	string language;
	string edition;
	string writer;
	float rating;
public:
	///functions set/get for all books types
	virtual void add_book()=0;
	string get_title();
	void set_title();
	void set_id(int);
	int get_id();
	int get_id_no_update();
	void set_price();
	float get_price();
	void set_genre();
	string get_genre();
	void set_release_date();
	void set_language();
	void set_edition();
	void set_writer();
	void set_rating();
	float get_rating();
	string get_release_date();
	string get_language();
	string get_edition();
	string get_writer();
	virtual ~Book()
	{

	}
};


class Paper_book : public Book
	///Paper_book is publicly derived class of Book class
{
protected:
	string publisher;
	int pages;
public:

	void set_publisher();
	void set_pages();
	string get_publisher();
	virtual void add_book();
	int get_pages();
	~Paper_book()
	{

	}
};

class Audio_cd : public Book
	///Audio_cd_book is publicly derived class of Book class
{
protected:
	string listening_length;
	string voice;
public:
	virtual void add_book();
	void set_voice();
	void set_listening_length();
	string get_listening_length();
	string get_voice();
	~Audio_cd()
	{

	}
};

class Digital_book : public Book
	///Digital_book is publicly derived class of Book class
{
	public:
	virtual void add_book();
	~Digital_book()
	{

	}
};

#endif
