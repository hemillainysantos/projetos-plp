#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

typedef struct{
	int points;
	int lifes;
	string nickname;
}player;

typedef struct{
	string name;
}level;

void start_score(player gamer) {
	gamer.points = 0;
}

void add_points(player gamer, level actual_level) {
	if (actual_level.name == "PYTHON") {
		gamer.points += 20;
	} else if (actual_level.name == "JAVA") {
		gamer.points += 30;
	} else if (actual_level.name == "ASSEMBLY") {
		gamer.points += 50;
	}
}

/* Set nickname's player
*/
void set_nickname(player gamer, string name) {
	gamer.nickname = name;
}

/* Set level
*/
void set_level(level actual_level, int round) {
	if (round <= 3) {
		actual_level.name = "PYTHON";
	} else if (round >= 4 && round <= 6) {
		actual_level.name = "JAVA";
	} else if (round >= 7 && round <= 10) {
		actual_level.name = "ASSEMBLY";
	}
}

/* This function add lifes to the player
 */
void add_lifes(player gamer, level actual_level) {
	if (actual_level.name == "PYTHON") {
		gamer.lifes += 7;
	} else if (actual_level.name == "JAVA") {
		gamer.lifes += 5;
	} else if (actual_level.name == "ASSEMBLY") {
		gamer.lifes += 3;
	}
}

void transfer_points(level actual_level, player winner_player, player loser_player) {
	int points;
	if (actual_level.name == "PYTHON") {
		points = loser_player.points * 0.1;
	} else if (actual_level.name == "JAVA") {
		points = loser_player.points * 0.15;
	} else if (actual_level.name == "ASSEMBLY") {
		points = loser_player.points * 0.2;
	}
	winner_player.points += points;
	loser_player.points -= points;
}

void penalize_player(level actual_level, player gamer) {
	int penalty;
	if (actual_level.name == "PYTHON") {
		penalty = 2;
	} else if (actual_level.name == "JAVA") {
		penalty = 5;
	} else if (actual_level.name == "ASSEMBLY") {
		penalty = 8;
	}
	gamer.points -= penalty;
	gamer.lifes -= 1;
}

string selection_word() {
	string word;
	cout << "Sorteando a palavra..." << endl;
	sleep(2);
	cout << "1" << endl;
	//pega uma palavra no arquivo
	return word;
}

vector<int> contains(string actual_word, char letter) {
    vector<int> index;
    for (int i = 0; i < actual_word.size(); i++) {
        if (actual_word[i] == letter) {
            index.push_back(i);
        }
    }
    return index;
}

string update_status_of_word(vector<int> index, string actual_status_of_word, char letter) {
	for (int i = 0; i < index.size(); i++) {
		actual_status_of_word[index[i]] = letter;
	}
	return actual_status_of_word;
}

string verify_letter(player gamer, char letter, level actual_level, string actual_word, string actual_status_of_word) {
	string result;
	vector<int> index = contains(actual_word, letter);
	if (index.size() != 0) {
        result = update_status_of_word(index, actual_status_of_word, letter);
	} else {
        penalize_player(actual_level, gamer);
        result = "A palavra não possui essa letra! Próximo:";
	}
	return result;
}



void model_word(int word_length, string actual_status_of_word) {
	for (int i = 0; i < word_length; i++) {
		actual_status_of_word += "_";
	}
}

void receive_letter(player gamer, level actual_level, string actual_word, string actual_status_of_word){
    char letter;
    cout << gamer.nickname + ", digite uma letra: ";
    cin >> letter;
    verify_letter(gamer, letter, actual_level, actual_word, actual_status_of_word);
}


int main() {
	// VARIAVEIS
	player player1, player2;
	level actual_level;
	bool state_game;
	int round_game;
	string actual_word;
	string actual_status_of_word;

	// INICIALIZANDO
	add_lifes(player1, actual_level);
	add_lifes(player2, actual_level);
	round_game = 1;
	set_level(actual_level, round_game);
	start_score(player1);
	start_score(player2);

	// DADOS JOGADORES
	cout << "Nome jogador 1: ";
	cin >> player1.nickname;

	cout << "Nome jogador 2: ";
	cin >> player2.nickname;

	state_game = player1.lifes != 0 || player2.lifes != 0;
    actual_word = selection_word();

	while (!state_game) {
		// SORTEANDO PALAVRA
		model_word(actual_word.size(), actual_status_of_word);

		// RECEBENDO UMA LETRA
		receive_letter(player1, actual_level, actual_word, actual_status_of_word);
		receive_letter(player2, actual_level, actual_word, actual_status_of_word);

	}
	return 0;
}
