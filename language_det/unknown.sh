#!/bin/zsh

set -x
grep ";Unknown" <pull_lang_detected.csv >pull_unknown

grep -v  ";\`\(.*\)\`;" <pull_unknown | grep -v ";\([a-z0-9]\+\)\{40\};" | grep -v "s/\(.*\)/\(.*\)" | grep -v -i ";.\?cc.\? \+@" | grep -v "; \?@\([a-zA-Z0-9]\)\+;" | grep -v -- "->" >pull1; mv pull1 pull_unknown

lang=Chinese

function g {
    grep "$@" <pull_unknown | sed "s|;Unknown|;$lang|g" >> pull_attach
    grep -v "$@" < pull_unknown > pull1; mv pull1 pull_unknown
}

g -P "[一-龥]"

lang=Japanese
g -P "([\x{4E00}-\x{9FBF}]|[\x{3040}-\x{309F}]|[\x{30A0}-\x{30FF}])+"  

lang=RUSSIAN

g -i -e "[ижлдяфбшычьэюйпцзвгнЩъщткУм]" -e "ок" -e "тут" -e "как"

lang=POLISH
g -i -e "[ąęłżźćńś]" -e "zrobione" -e "zrobilas" -e "wywal" -e "wystarczy"

lang=FRENCH
g -i -e "je n'ai" -e "l'a" -e "merci" -e "Ça" -e ";oui;" -e "c'est" -e "n'e"
g -i -e ";je \(.*\)\+" -e "du coup"

lang=GERMAN
g -i -e "[üß]" -e "alles"
g -e ";Ich \(.*\)\+" -e ";Du \(.*\)\+t" -e "[B|b]itte" -e "[A|a]uch " -e " \?[N|n]icht "

lang=SPANISH
g -i -e "bien.\?"

lang=VIETNAMESE
g -i -e "ỏ" -e "Cảm"

grep -P -v "[\x80-\xFF]" <pull_unknown >pull1; mv pull1 pull_unknown


lang=ENGLISH

g -i -e "LGTM" -e "Thank" -e "Yep\." -e "Done.\?" -e "n't" -e "'ll" -e "I'm" -e "It's" -e "what" -e "why" -e "same as" -e ";Fixed.\?" -e "see" -e "good " -e "removed" -e ";ok.\?;" -e ";no.\?" -e "changed.\?" -e "again " -e "works for" -e "you \?" -e "delete" -e "semicolon" -e ";yep.\?" -e "yup.\?" -e "you're" -e "fixed" -e " for " -e "sense" -e "love" -e "nice" -e "thx" -e "will " -e "ing" -e "about" -e "above" -e "add" -e "again" -e "agree" -e "cool" -e "sorry" -e "align" -e "please" -e "also" -e "better" -e "excellent" -e "perfect" -e "broken" -e "this" -e "remove" -e "awesome" -e "here" -e "ditto" -e "sure" -e "typo" -e "solve" -e "accept" -e "fix" -e "line" -e "space" -e "yes" -e "yeah" -e "wtf" -e ";use" -e "very" -e "wrong" -e "I see" -e "ah,\? " -e ";\?made " -e "more " -e "need" -e "at's" -e "which" -e "when" -e "because"

g -i -e "change" -e "understood" -e " \?try "

g -e ";I \(.*\)\+" -e ";It \(.*\)\+" -e ";it \(.*\)\+" -e "its " -e "I'd \(.*\)\+"

g -i -e "update" -e "that " -e "actually" -e "right" -e "gotcha" -e "sweet" -e "strange" -e "clean" -e "should" -e "would" -e " \?and "

g -i -e "dotfiles" -e "homepage" -e "browser"

g -i "\(.*\)\+ed "

grep -i -e ";\(:+1: \)\+\?;" -e ";:+1:;" -e ";+1;" -e ";:);" -e ";:(;" -e ";:D;" -e ";:P;" -e ";\(:[a-zA-Z)(0-9\*\^_]\+:\)\+\?;"  <pull_unknown | sed 's|;Unknown|;EMOJI|g' >>pull_emoji
grep -i -v -e ";\(:+1: \)\+\?;" -e ";:+1:;" -e ";+1;" -e ";:);" -e ";:(;" -e ";:D;" -e ";:P;" -e ";\(:[a-zA-Z)(0-9\*\^_]\+:\)\+\?;" <pull_unknown >pull1; mv pull1 pull_unknown

grep ";:\?+1" <pull_unknown | sed 's|;Unknown|;EMOJI|g' >>pull_emoji
grep -v ";:\?+1" <pull_unknown >pull1; mv pull1 pull_unknown

grep ";\([?-+|(&%#$;,.?:1*{} =\`><@]\+\)\+\?;" <pull_unknown | sed 's|;Unknown|;EMOJI|g' >>pull_emoji
grep -v ";\([?-+|(&%#$;,.?:1*{} =\`><@]\+\)\+\?;" <pull_unknown >pull1; mv pull1 pull_unknown

grep -e  ";:\(.*\): :\(.*\):;" -e ";:\(.*\): :\(.*\): \(.*\);" <pull_unknown  | sed 's|;Unknown|;EMOJI|g' >>pull_emoji
grep -v -e ";:\(.*\): :\(.*\):;" -e ";:\(.*\): :\(.*\): \(.*\);" <pull_unknown >pull1; mv pull1 pull_unknown

grep -e ";\(:[a-zA-Z0-9\*\^\_\ ]\+:\) \+\?;" -e ";\(:[a-zA-Z0-9\*\^\_\ ]\+:\)\+\?;" -e ";-1;" <pull_unknown | sed 's|;Unknown|;EMOJI|g' >>pull_emoji
grep -v -e";\(:[a-zA-Z0-9\*\^\_\ ]\+:\) \+\?;" -e ";\(:[a-zA-Z0-9\*\^\_\ ]\+:\)\+\?;"  <pull_unknown >pull1; mv pull1 pull_unknown
grep -i -e ";a\+r\+g\+h\+" -e ";uhh\?\+;" <pull_unknown | sed 's|;Unknown|;EMOJI|g' >>pull_emoji
grep -i -v -e ";a\+r\+g\+h\+" -e ";uhh\?\+;" <pull_unknown >pull1; mv pull1 pull_unknown

#bengali
#grep -P "([\x{0980}-\x{09FF}])+"

#grep -P "[\x80-\xFF]" <pull_unknown >dziady

grep -v ";[-0-9. ]\+;" <pull_unknown >pull1; mv pull1 pull_unknown

awk -F ";" '{print $2}' <pull_unknown| sort | uniq >pull_unknown_sorted
