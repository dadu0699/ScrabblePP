#include "Menu.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
// #include <typeinfo>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

Menu::Menu()
{
	players = new BinarySearchTree();

	boardDimensions = 0;
	turn = false;

	principal();
}

Menu::~Menu()
{
}

void Menu::principal()
{
	int option;
	bool loop = true;
	while (loop)
	{
		cout << endl
			 << "\tMenu Principal";
		cout << endl
			 << "\t1. Iniciar";
		cout << endl
			 << "\t2. Escoger / Agregar / Reporte Jugadores";
		cout << endl
			 << "\t3. Tablero de puntuacion";
		cout << endl
			 << "\t4. Salir";
		cout << endl
			 << "\t >> ";
		cin >> option;

		switch (option)
		{
		case 1:
			if (playerOne != nullptr && playerTwo != nullptr)
			{
				string word;
				cout << endl
					 << "\tArchivo JSON: ";
				cin >> word;
				readJSON(word);

				if (board != nullptr && dictionary != nullptr)
				{
					startGame();
				}
			}
			break;
		case 2:
			choosePlayer();
			break;
		case 3:
			players->scoreBoard();
			break;
		case 4:
			cout << endl
				 << "\tSALIENDO!!!!!!!!!!!!!!";
			loop = false;
			break;
		default:
			cout << endl
				 << "\tOPCION INCORRECTA";
			cout << endl;
			break;
		}
		system("CLS");
	}
}

void Menu::choosePlayer()
{
	string namePlayerOne;
	bool flagPlayerOne = false;

	string namePlayerTwo;
	bool flagPlayerTwo = false;

	int option;
	bool loop = true;

	while (!flagPlayerOne || !flagPlayerTwo)
	{
		cout << endl
			 << "\t1. Escoger jugador";
		cout << endl
			 << "\t2. Agregar Jugador";
		cout << endl
			 << "\t3. Reporte Jugadores";
		cout << endl
			 << "\t4. Puntuacion Jugador";
		cout << endl
			 << "\t >> ";
		cin >> option;

		switch (option)
		{
		case 1:
			if (!flagPlayerOne)
			{
				cout << "\t >> Jugador 1: ";
				cin >> namePlayerOne;
				playerOne = players->search(namePlayerOne);
				if (playerOne == nullptr)
				{
					cout << "\t El jugador " << namePlayerOne << " no se ha registrado previamente" << endl;
				}
				else
				{
					flagPlayerOne = true;
				}
			}

			if (!flagPlayerTwo)
			{
				cout << "\t >> Jugador 2: ";
				cin >> namePlayerTwo;
				playerTwo = players->search(namePlayerTwo);
				if (playerTwo == nullptr)
				{
					cout << "\t El jugador: " << namePlayerTwo << " no se ha registrado previamente" << endl;
				}
				else
				{
					flagPlayerTwo = true;
				}
			}
			break;
		case 2:
			if (!flagPlayerOne)
			{
				playerOne = new Player("");
				cout << "\t >> Jugador 1: ";
				cin >> namePlayerOne;
				playerOne->setName(namePlayerOne);
				flagPlayerOne = players->addNode(playerOne);
				if (!flagPlayerOne)
				{
					cout << "\t El juador " << namePlayerOne << " se ha registrado previamente" << endl;
				}
			}

			if (!flagPlayerTwo)
			{
				playerTwo = new Player("");
				cout << "\t >> Jugador 2: ";
				cin >> namePlayerTwo;
				playerTwo->setName(namePlayerTwo);
				flagPlayerTwo = players->addNode(playerTwo);
				if (!flagPlayerTwo)
				{
					cout << "\t El juador: " << namePlayerTwo << " se ha registrado previamente" << endl;
				}
			}
			break;
		case 3:
			players->report();
			players->reportPreOrder();
			players->reportInOrder();
			players->reportPostOrder();
			return;
		case 4:
			cout << "\t >> Jugador: ";
			cin >> namePlayerOne;
			playerOne = players->search(namePlayerOne);
			if (playerOne == nullptr)
			{
				cout << "\t El juador " << namePlayerOne << " no se ha registrado previamente" << endl;
			}
			else
			{
				playerOne->getScores()->report();
			}
			playerOne = nullptr;
			cout << endl
				 << "\t";
			system("pause");
			return;
		default:
			cout << endl
				 << "\tOPCION INCORRECTA";
			cout << endl;
			break;
		}

		if (playerOne == playerTwo)
		{
			flagPlayerOne = false;
			flagPlayerTwo = false;
			cout << endl
				 << "\t No se puede escoger dos veces el mismo jugador";
		}
		cout << endl;
	}
	system("CLS");
}

void Menu::startGame()
{
	system("CLS");
	DoubleList lettersPlayerOne;
	DoubleList lettersPlayerTwo;
	DoubleList auxLetters;
	int option;
	char tile;
	string word;
	string cW;
	int positionX;
	int positionY;
	int postions[25][2];
	int playerOneScore;
	int playerTwoScore;
	int coordinateX;
	int coordinateY;
	bool finish;

	word = "";
	playerOneScore = 0;
	playerTwoScore = 0;
	coordinateX = boardDimensions / 2;
	coordinateY = boardDimensions / 2;
	finish = false;
	letters = new Queue();

	for (int i = 0; i < 7; i++)
	{
		lettersPlayerOne.addLastNode(letters->pop()->getLetter());
		lettersPlayerTwo.addLastNode(letters->pop()->getLetter());
	}

	while (!finish)
	{
		word.clear();
		if (turn)
		{
			cout << endl
				 << "\tTurno jugador 1: "
				 << playerOne->getName();
			lettersPlayerOne.report();
		}
		else
		{
			cout << endl
				 << "\tTurno jugador 2: "
				 << playerTwo->getName();
			lettersPlayerTwo.report();
		}

		cout << endl
			 << "\t1. Agregar ficha";
		cout << endl
			 << "\t2. Intercambiar fichas";
		cout << endl
			 << "\t3. Terminar Partida";
		cout << endl
			 << "\t >> ";
		cin >> option;

		if (turn)
		{
			// Player One
			switch (option)
			{
			case 1:
				do
				{
					cout << endl
						 << "\t >> ficha: ";
					cin >> tile;
					cout << "\t >> Posicion x: ";
					cin >> positionX;
					cout << "\t >> Posicion y: ";
					cin >> positionY;

					if (positionX <= boardDimensions && positionX > 0 && positionY <= boardDimensions && positionY > 0)
					{
						if (positionX >= coordinateX && positionY >= coordinateY)
						{

							if (board->getNode(positionX, positionY) != nullptr)
							{
								if (board->getNode(positionX, positionY)->getData()[0] == tile)
								{
									cout << "\t Se reutilizara la letra ya colocada en el tablero : "
										 << tile;

									word += tile;
									postions[word.length() - 1][0] = positionX;
									postions[word.length() - 1][1] = positionY;
									coordinateX = positionX;
									coordinateY = positionY;
								}
								else if (board->getNode(positionX, positionY)->getData() == "")
								{
									if (lettersPlayerOne.searchNode(tile) != nullptr)
									{
										auxLetters.addLastNode(lettersPlayerOne.searchNode(tile)->getLetter());
										lettersPlayerOne.deleteSpecificNode(tile);

										word += tile;
										postions[word.length() - 1][0] = positionX;
										postions[word.length() - 1][1] = positionY;
										coordinateX = positionX;
										coordinateY = positionY;
									}
									else
									{
										cout << "\t Ficha no encontrada: " << tile;
									}
								}
								else
								{
									cout << "\t No se puede remplazar la letra";
								}
							}
							else
							{
								if (lettersPlayerOne.searchNode(tile) != nullptr)
								{
									auxLetters.addLastNode(lettersPlayerOne.searchNode(tile)->getLetter());
									lettersPlayerOne.deleteSpecificNode(tile);

									word += tile;
									postions[word.length() - 1][0] = positionX;
									postions[word.length() - 1][1] = positionY;
									coordinateX = positionX;
									coordinateY = positionY;
								}
								else
								{
									cout << "\t Ficha no encontrada: " << tile;
								}
							}
						}
						else
						{
							cout << "\t Coordenada fuera de rango: (" << positionX << ","
								 << positionY << ") para formar una palbra de D-I o Ar-Ab";
						}
					}
					else
					{
						cout << "\t Coordenada fuera de rango: (" << positionX << "," << positionY << ")";
					}

					cout << endl
						 << "\t >> Desea continuar (s/n): ";
					cin >> tile;
				} while (tile == 's');

				if (dictionary->searchNode(word) != nullptr)
				{
					for (int i = 0; i < word.length(); i++)
					{
						cW = word.at(i);
						if (board->getNode(postions[i][0], postions[i][1]) != nullptr)
						{
							if (board->getNode(postions[i][0], postions[i][1])->getData() == "")
							{
								board->getNode(postions[i][0], postions[i][1])->setData(cW);
								playerOneScore += board->getNode(postions[i][0], postions[i][1])->getScore() * auxLetters.getFirstNode()->getLetter()->getScore();
							}
						}
						else
						{
							board->addNode(postions[i][0], postions[i][1], 1, cW);
							playerOneScore += auxLetters.getFirstNode()->getLetter()->getScore();

							lettersPlayerOne.addLastNode(letters->pop()->getLetter());
							auxLetters.deleteFirstNode();
						}
					}
					board->report();
				}
				else
				{
					cout << endl
						 << "\t Palabra no encontrada: " << word;

					while (!auxLetters.isEmpty())
					{
						lettersPlayerOne.addLastNode(auxLetters.getLastNode()->getLetter());
						auxLetters.deleteLastNode();
					}
				}
				break;
			case 2:
				do
				{
					cout << endl
						 << "\t >> ficha: ";
					cin >> tile;
					if (lettersPlayerOne.searchNode(tile) != nullptr)
					{
						letters->push(lettersPlayerOne.searchNode(tile)->getLetter());
						lettersPlayerOne.deleteSpecificNode(tile);
						lettersPlayerOne.addLastNode(letters->pop()->getLetter());
					}
					else
					{
						cout << "\t Ficha no encontrada: " << tile;
					}

					cout << endl
						 << "\t >> Desea continuar (s/n): ";
					cin >> tile;
				} while (tile == 's');
				lettersPlayerOne.report();
				cout << endl
					 << "\t";
				system("pause");
				break;
			case 3:
				finish = true;
				break;
			default:
				cout << endl
					 << "\tOPCION INCORRECTA";
				cout << endl;
				break;
			}
		}
		else
		{
			// Player Two
			switch (option)
			{
			case 1:
				do
				{
					cout << endl
						 << "\t >> ficha: ";
					cin >> tile;
					cout << "\t >> Posicion x: ";
					cin >> positionX;
					cout << "\t >> Posicion y: ";
					cin >> positionY;

					if (positionX <= boardDimensions && positionX > 0 && positionY <= boardDimensions && positionY > 0)
					{
						if (positionX >= coordinateX && positionY >= coordinateY)
						{

							if (board->getNode(positionX, positionY) != nullptr)
							{
								if (board->getNode(positionX, positionY)->getData()[0] == tile)
								{
									cout << "\t Se reutilizara la letra ya colocada en el tablero : "
										 << tile;

									word += tile;
									postions[word.length() - 1][0] = positionX;
									postions[word.length() - 1][1] = positionY;
									coordinateX = positionX;
									coordinateY = positionY;
								}
								else if (board->getNode(positionX, positionY)->getData() == "")
								{
									if (lettersPlayerTwo.searchNode(tile) != nullptr)
									{
										auxLetters.addLastNode(lettersPlayerTwo.searchNode(tile)->getLetter());
										lettersPlayerTwo.deleteSpecificNode(tile);

										word += tile;
										postions[word.length() - 1][0] = positionX;
										postions[word.length() - 1][1] = positionY;
										coordinateX = positionX;
										coordinateY = positionY;
									}
									else
									{
										cout << "\t Ficha no encontrada: " << tile;
									}
								}
								else
								{
									cout << "\t No se puede remplazar la letra";
								}
							}
							else
							{
								if (lettersPlayerTwo.searchNode(tile) != nullptr)
								{
									auxLetters.addLastNode(lettersPlayerTwo.searchNode(tile)->getLetter());
									lettersPlayerTwo.deleteSpecificNode(tile);

									word += tile;
									postions[word.length() - 1][0] = positionX;
									postions[word.length() - 1][1] = positionY;
									coordinateX = positionX;
									coordinateY = positionY;
								}
								else
								{
									cout << "\t Ficha no encontrada: " << tile;
								}
							}
						}
						else
						{
							cout << "\t Coordenada fuera de rango: (" << positionX << ","
								 << positionY << ") para formar una palbra de D-I o Ar-Ab";
						}
					}
					else
					{
						cout << "\t Coordenada fuera de rango: (" << positionX << "," << positionY << ")";
					}

					cout << endl
						 << "\t >> Desea continuar (s/n): ";
					cin >> tile;
				} while (tile == 's');

				if (dictionary->searchNode(word) != nullptr)
				{
					for (int i = 0; i < word.length(); i++)
					{
						cW = word.at(i);
						if (board->getNode(postions[i][0], postions[i][1]) != nullptr)
						{
							if (board->getNode(postions[i][0], postions[i][1])->getData() == "")
							{
								board->getNode(postions[i][0], postions[i][1])->setData(cW);
								playerTwoScore += board->getNode(postions[i][0], postions[i][1])->getScore() * auxLetters.getFirstNode()->getLetter()->getScore();
							}
						}
						else
						{
							board->addNode(postions[i][0], postions[i][1], 1, cW);
							playerTwoScore += auxLetters.getFirstNode()->getLetter()->getScore();
							lettersPlayerTwo.addLastNode(letters->pop()->getLetter());
							auxLetters.deleteFirstNode();
						}
					}
					board->report();
				}
				else
				{
					cout << endl
						 << "\t Palabra no encontrada: " << word;

					while (!auxLetters.isEmpty())
					{
						lettersPlayerTwo.addLastNode(auxLetters.getLastNode()->getLetter());
						auxLetters.deleteLastNode();
					}
				}
				break;
			case 2:
				do
				{
					cout << endl
						 << "\t >> ficha: ";
					cin >> tile;
					if (lettersPlayerTwo.searchNode(tile) != nullptr)
					{
						letters->push(lettersPlayerTwo.searchNode(tile)->getLetter());
						lettersPlayerTwo.deleteSpecificNode(tile);
						lettersPlayerTwo.addLastNode(letters->pop()->getLetter());
					}
					else
					{
						cout << endl
							 << "\t Ficha no encontrada: " << tile;
					}

					cout << endl
						 << "\t >> Desea continuar (s/n): ";
					cin >> tile;
				} while (tile == 's');
				lettersPlayerTwo.report();
				cout << endl
					 << "\t";
				system("pause");
				break;
			case 3:
				finish = true;
				break;
			default:
				cout << endl
					 << "\tOPCION INCORRECTA";
				cout << endl;
				break;
			}
		}
		letters->report();
		turn = !turn;
		coordinateX = 0;
		coordinateY = 0;
	}

	playerOne->getScores()->addLastNode(playerOneScore);
	playerTwo->getScores()->addLastNode(playerTwoScore);

	if (playerOneScore > playerTwoScore)
	{
		cout << endl
			 << "\t >> Ganador: " << playerOne->getName() << " " << playerOneScore;
		cout << endl
			 << "\t >> Segundo: " << playerTwo->getName() << " " << playerTwoScore;
	}
	else if (playerOneScore < playerTwoScore)
	{
		cout << endl
			 << "\t >> Ganador: " << playerTwo->getName() << " " << playerTwoScore;
		cout << endl
			 << "\t >> Segundo: " << playerOne->getName() << " " << playerOneScore;
	}
	else
	{
		cout << endl
			 << "\t >> Empate";
		cout << endl
			 << "\t >> Jugador 1: " << playerOne->getName() << " " << playerOneScore;
		cout << endl
			 << "\t >> Jugador 2: " << playerTwo->getName() << " " << playerTwoScore;
	}
	cout << endl
		 << "\t";
	system("pause");
}

void Menu::readJSON(string route)
{
	ifstream jsonFile(route);
	if (jsonFile.is_open())
	{
		board = new SparseMatrix();
		dictionary = new CircularDoubleList();

		json jsonData;
		jsonFile >> jsonData;

		int x;
		int y;

		boardDimensions = jsonData.at("dimension");
		cout << "Dimension: " << boardDimensions << endl;
		cout << "Casillas: " << endl;
		cout << "\tDobles: " << endl;
		for (size_t i = 0; i < jsonData.at("casillas").at("dobles").size(); i++)
		{
			x = jsonData.at("casillas").at("dobles")[i].at("x");
			y = jsonData.at("casillas").at("dobles")[i].at("y");
			board->addNode(x, y, 2, "");

			cout << "\t\tX: " << x << endl;
			cout << "\t\tY: " << y << endl;
		}
		cout << "\tTriples: " << endl;
		for (size_t i = 0; i < jsonData.at("casillas").at("triples").size(); i++)
		{
			x = jsonData.at("casillas").at("triples")[i].at("x");
			y = jsonData.at("casillas").at("triples")[i].at("y");
			board->addNode(x, y, 3, "");

			cout << "\t\tX: " << x << endl;
			cout << "\t\tY: " << y << endl;
		}

		cout << "Diccionario: " << endl;
		for (size_t i = 0; i < jsonData.at("diccionario").size(); i++)
		{
			cout << "\tPalabra: " << jsonData.at("diccionario")[i].at("palabra") << endl;
			dictionary->addNode(jsonData.at("diccionario")[i].at("palabra"));
		}
		dictionary->report();
		board->report();
	}
	else
	{
		cout << "Unable to open file" << endl;
	}
}

void Menu::assignTurn()
{
	if (rand() % 2 == 1)
	{
		turn = true;
	}
	else
	{
		turn = false;
	}
}
