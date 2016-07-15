#!/usr/bin/python

import math

import string

import sys

def readfile(filename):
    '''
    return a list of lines of the file
    :param filename:
    :return:
    '''
    try:
        f = open(filename, 'r')
        return f.read()
    except IOError:
        print("Error opending or reading file: ", filename)
        sys.exit(-1)


translation_table = str.maketrans(string.punctuation,
                                     " " * len(string.punctuation))


def get_words_from_line_list(text):
    text.lower()
    text = text.translate(translation_table)
    word_list = text.split()
    return word_list


def count_frequency(word_list):
    d = {}
    for word in word_list:
        if word in d:
            d[word] += 1
        else:
            d[word] = 1
    return d


def word_frequencies_for_file(filename):
    line_list = readfile(filename)
    word_list = get_words_from_line_list(line_list)
    word_freq = count_frequency(word_list)

    print(len(line_list), "length of file")
    print(len(word_list), "# of words")

    return word_freq


def inner_product(d1,d2):
    sum = 0.0
    for key in d1:
        if key in d2:
            print ("same key:", key)
            sum += (d1[key] * d2[key])
    print("inner product:", sum)
    return sum


def vector_angle(d1,d2):
    numerator = inner_product(d1, d2)
    denominator = math.sqrt(inner_product(d1,d1) * inner_product(d2,d2))
    print("numerator: ", numerator)
    print("denominator: ", denominator)
    return math.acos(numerator / denominator)


def main():
    if len(sys.argv) != 3:
        print ("Usage: docdist.py filename_1 filename_2")
    else:
        filename_1 = sys.argv[1]
        filename_2 = sys.argv[2]
        sorted_word_list_1 = word_frequencies_for_file(filename_1)
        sorted_word_list_2 = word_frequencies_for_file(filename_2)
        distance = vector_angle(sorted_word_list_1,sorted_word_list_2)
        print ("The distance between the documents is: %0.6f (radians)"%distance)


if __name__ == "__main__":
    import profile
    profile.run("main()")




