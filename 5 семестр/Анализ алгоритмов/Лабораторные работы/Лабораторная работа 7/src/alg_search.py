def full_search(key, dictionary):
    keys = list(dictionary.keys())

    for i in range(len(keys)):
        if keys[i] == key:
            return dictionary[key], i + 1


def binary_search(key, dictionary):
    keys = list(dictionary.keys())

    cnt = 0
    min_i = 0
    max_i = len(keys)

    while min_i <= max_i:
        cnt += 1

        middle_i = (max_i + min_i) // 2
        cur_key = keys[middle_i]

        if cur_key == key:
            cnt += 1

            return dictionary[cur_key], cnt

        elif key < cur_key:
            max_i = middle_i - 1
        else:
            min_i = middle_i + 1

        cnt += 2


def segment_search(key, segmented_dict):
    letters = list(segmented_dict.keys())

    cnt = 0

    for letter in letters:
        cnt += 1  

        if key[0] == letter:
            cnt += 1  
            res = binary_search(key, segmented_dict.get(letter))

            if res is not None:
                return res[0], cnt + res[1]
