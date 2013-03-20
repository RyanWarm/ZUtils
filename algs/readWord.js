// You have a sentence with several words with spaces
// removed and words having their character order
// shuffled. You have a dictionary. Write an algorithm
// to produce the sentence back with spaces and words
// with normal character order
 
function Result(){}
 
function Success(words, remaining) {
    this.words = words;
    this.remaining = remaining;
}
 
Success.prototype = new Result();
 
function Failure(source) {
    this.source = source;
}
 
Failure.prototype = new Result();
 
function readWordFrom(word) {
    function canonize(w) {
        var arr = w.split('');
        arr.sort();
        return arr.join('');
    }
 
    return function readWord(source) {
        var word_key = canonize(word);
        var source_key = canonize(source.slice(0, word.length));
 
        if (word_key === source_key) {
            return new Success([word], source.slice(word.length));
        } else {
            return new Failure(source);
        }
    };
}
 
function readOneOf(dictionary) {
    return function read(source) {
        var i = dictionary.length,
            result;
 
        while (i--) {
            result = readWordFrom(dictionary[i])(source);
            if (result instanceof Success) {
                return result;
            }
        }
 
        return new Failure(source); 
    };
}
 
function zeroOrMore(parser) {
    return function (source) {
        var results = [];
        var result;
 
        while ((result = parser(source)) instanceof Success) {
            [].push.apply(results, result.words);
            source = result.remaining;
        }
 
        return new Success(results, source);
    };
}
 
function exactly(parser) {
    return function (source) {
        var result = parser(source),
            isComplete;
 
        if (result instanceof Success &&
            result.remaining === '') {
            return result;
        } else {
            return new Failure(source);
        }
    };
}
 
function readWords(dictionary) {
    return exactly(zeroOrMore(readOneOf(dictionary)));
}
 
exports.readWords = function (dictionary, source) {
    var result = readWords(dictionary)(source);
    if (result instanceof Success) {
        return result.words;
    } else {
        throw new Error('Source is not composed of words from this dictionary');
    }
}
 
(function runTests() {
    var assert = require('assert');
 
    assert.ok(readWordFrom('okay')('okayrest') instanceof Success);
    assert.deepEqual(readWordFrom('okay')('okayrest').words, ['okay']);
    assert.deepEqual(readWordFrom('okay')('okayrest').remaining, 'rest');
 
    assert.ok(readWordFrom('okay')('notokay') instanceof Failure);
    assert.deepEqual(readWordFrom('okay')('notokay').source, 'notokay');
 
    // read yes, no or maybe from 'yesrest'
    assert.ok(readOneOf(['yes', 'no', 'maybe'])('yesrest') instanceof Success);
    assert.deepEqual(readOneOf(['yes', 'no', 'maybe'])('yesrest').words, ['yes']);
    assert.deepEqual(readOneOf(['yes', 'no', 'maybe'])('yesrest').remaining, 'rest');
 
    // read yes, no or maybe from 'norest'
    assert.ok(readOneOf(['yes', 'no', 'maybe'])('norest') instanceof Success);
    assert.deepEqual(readOneOf(['yes', 'no', 'maybe'])('norest').words, ['no']);
    assert.deepEqual(readOneOf(['yes', 'no', 'maybe'])('norest').remaining, 'rest');
 
    // read yes, no or maybe from 'mayberest'
    assert.ok(readOneOf(['yes', 'no', 'maybe'])('mayberest') instanceof Success);
    assert.deepEqual(readOneOf(['yes', 'no', 'maybe'])('mayberest').words, ['maybe']);
    assert.deepEqual(readOneOf(['yes', 'no', 'maybe'])('mayberest').remaining, 'rest');
 
    // read yes, no, or maybe from 'failrest'
    assert.ok(readOneOf(['yes', 'no', 'maybe'])('failrest') instanceof Failure);
    assert.deepEqual(readOneOf(['yes', 'no', 'maybe'])('failrest').source, 'failrest');
 
    var dictionary = ['one', 'two', 'three'];
    assert.ok(readWords(dictionary)('fail') instanceof Failure);
    assert.ok(readWords(dictionary)('onetwo') instanceof Success);
    assert.deepEqual(readWords(dictionary)('onetwo').words,
                     ['one', 'two']);
 
    assert.ok(readWords(dictionary)('oenwot') instanceof Success);
    assert.deepEqual(readWords(dictionary)('oenwot').words,
                     ['one', 'two']);
 
    assert.ok(readWords(dictionary)('oenwotfail') instanceof Failure);
    assert.deepEqual(readWords(dictionary)('oenwotfail').source, 'oenwotfail');
}());