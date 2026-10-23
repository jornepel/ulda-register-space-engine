WIJ REKENEN NIET MET NULLEN — Het Kompas en de Twaalf Raadsels

Auteur: Jorne Pel
Status: ~B (theorie, geen bewijs — wacht op peer review)
Over dit document

Dit is een theorie, geen bewijs.

De wiskunde in dit document is na te rekenen. De probleemstellingen zijn gedocumenteerd en peer-reviewed (✓). Maar de interpretaties — de indeling van de raadsels, de lezing door het kompas — zijn dat niet. Die zijn intern consistent, maar niemand heeft ze onafhankelijk getoetst. Daarom zijn ze ~B.

En er is een derde laag: de vraag of dit iets zegt over de fysieke werkelijkheid. Daar is geen experimentele toets voor. Die laag is ?-O.

Dit document lost de raadsels niet op. Het stelt één vraag: is het juiste gereedschap gekozen? En het geeft bij elk antwoord eerlijk de graad.
Samenvatting

We rekenen in base-10. Dat is een keuze, geen natuurwet — waarschijnlijk omdat we tien vingers hebben.

Die keuze heeft een nadeel. Deel je 1 door 3, dan krijg je 0,3333... dat nooit stopt. Je moet afronden, en afronden betekent dat je een klein beetje rommel meeneemt in je berekening. Bij één deling is dat te overzien. Bij een lange keten van berekeningen telt die rommel op.

Dit stuk stelt een simpele vraag: wat als we voor sommige problemen rekenen met zestig in plaats van tien?

Zestig is deelbaar door 1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30 en 60 — twaalf delers. Daardoor vallen breuken zoals 1/3 en 1/6 direct precies uit, zonder afronding.

Maar dit stuk zegt niet dat base-10 fout is. Base-10 is prima voor alles wat recht is: afstand, gewicht, geld, tijd. Het zegt iets anders: voor ronde problemen — hoeken, rotatie, stroming, bollen — is een cyclisch gereedschap mogelijk beter.

En de grote raadsels in de wiskunde en natuurkunde zijn voor een groot deel ronde problemen.
Deel 1 — De these
1.1 Twee soorten gereedschap

Er zijn twee manieren om te rekenen, en ze zijn allebei goed.

Lineair (base-10). Je meet van A naar B. Afstand, gewicht, geld, stappen, tijd. Je legt een lat, je meet, je zaagt. Zaag je een millimeter te veel, dan zaag je dat aan het eind recht. Base-10 is hier genoeg.

Cyclisch (base-60). Je meet hoeken, rotatie, stroming, bollen. Hier is geen begin en geen eind, dus een rechte lat werkt niet. Je hebt een mal nodig die de bocht al kent. Base-60 is hier beter.

De wereld gebruikt ze allebei al. Base-10 voor geld. Base-60 voor tijd: 60 minuten, 60 seconden, 360 graden. Dat is geen toeval — elk gereedschap heeft zijn eigen klus.
1.2 De these

    De wiskunde is lineair geworden. De sterrenkunde is cyclisch gebleven. En de raadsels zijn voor een groot deel cirkelproblemen. Dus worden die raadsels met het verkeerde gereedschap opgeschreven.

Dat is de these. Niet "we rekenen fout", maar "we pakken het verkeerde gereedschap voor ronde problemen".
1.3 Waarom heeft niemand het gedaan?

Omdat de wiskunde lineair is geworden. De sterrenkunde bleef cyclisch, want de hemel draait — daar bleef base-60: 60 minuten, 360 graden. Maar de wiskunde werd analysis, algebra, de getallenlijn. Daar kwam base-10.

En de raadsels? Die gaan over rotatie, stroming, golven, bollen. Die zijn cyclisch. Maar ze worden in base-10 opgeschreven.

Dat is de these. En ze is testbaar.
Deel 2 — Het gereedschap
2.1 Waarom zestig?

Tien is 2 × 5. Vier delers: 1, 2, 5, 10.
Zestig is 2 × 2 × 3 × 5. Twaalf delers: 1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30, 60.

Dat verschil is het hele verhaal. Met zestig heb je meer grip op je materiaal. 1/3 = 0.20 in base-60, 1/6 = 0.10 — precies, zonder rest. Alleen 1/7 blijft oneindig doorlopen, want 60 is niet deelbaar door 7.

Dat laatste is belangrijk: base-60 lost niet alle breuken op. Het lost de breuken op die voor de bol van belang zijn.
2.2 De vijf functies, de operator, en de vijf vormen

De getallen 1 tot en met 5 zijn de vijf Platonische lichamen. De 6 is de operator, de brug tussen mal en vorm.

    1 = oorsprong (tetraëder)

    2 = deler (kubus)

    3 = drie assen (octaëder)

    4 = vier hoeken (icosaëder)

    5 = stappen (dodecaëder)

    6 = operator (de brug)

De keten loopt: 1 → 2 → 3 → 4 → 5 → 6 → 60 → 360.

En de bol klopt op twee manieren:
text

6 × 60 = 360 (lineair)
5 × 72 = 360 (cyclisch)

Beide zijn waar. De ene is lineair, de andere cyclisch. Samen vertellen ze het verhaal van de bol.
2.3 De Euler-karakteristiek

De vijf Platonische lichamen zijn niet zomaar vormen. Ze volgen de topologische wet van Euler:
text

V − E + F = 2   (hoekpunten − ribben + vlakken = 2)

Nemen we de twee meest complexe lichamen — de dodecaëder (functie 5) en de icosaëder (functie 4) — en halen we ze door de operator (6), dan gebeurt dit:

Dodecaëder (functie 5):

    12 vlakken × 6 = 72. Dat is precies de rotatiesector: 360° / 5.

    30 ribben × 12 = 360. Dat is de volle bol.

    Euler: 20 − 30 + 12 = 2. ✓

Icosaëder (functie 4):

    20 vlakken × 6 = 120. Dat is 2 × 60, twee roll-overs.

    12 hoekpunten. Dat is de spiegelas.

    Euler: 12 − 30 + 20 = 2. ✓

Wat dit laat zien: de geometrie van de Platonische lichamen, door de operator gehaald, levert precies de rotatiesectoren en spiegelassen van de 360°-bol. Dat is een narekenbare structuur — een fenomeen (✓). Dat dit de bedoeling van de bol is, is een interpretatie (~). Zie §5.
Deel 3 — Twee voorbeelden
3.1 Navier-Stokes

De vraag: bestaan er altijd gladde oplossingen voor de Navier-Stokes-vergelijkingen in drie dimensies, of kunnen er singulariteiten ontstaan? Onbewezen sinds 1934.

De vergelijkingen:
text

∂u/∂t + (u · ∇)u = -∇p/ρ + ν∇²u
∇ · u = 0

De base-60 weergave:
text

24.120 + 12.500 = 36.620

Eerlijkheid voorop: 24.120 en 12.500 zijn gekozen getallen. Ze komen niet uit Navier-Stokes. Ze komen uit het register (24.120 = 67 × 360; 12.500 = 4 × 5⁵).

Wat dit voorbeeld laat zien: dat een lange formule kort kan worden in base-60. Niet dat Navier-Stokes oplost. Dat is een illustratie (~), geen afleiding (✓).
3.2 Poincaré

De vraag: is elke gesloten, enkelvoudig verbonden 3-manifold homeomorf aan een 3-sfeer? Bewezen door Grigori Perelman in 2003.

De formule:
text

π₁(M) = 0 → M ≅ S³

De base-60 weergave:
text

8 × 9 = 72
5 × 72 = 360

Eerlijkheid: 72 komt niet uit Poincaré. Het komt uit het register (8 × 9 = 72, en 360/5 = 72).

Wat dit voorbeeld laat zien: dat een 3-bol (360°) opgebouwd kan worden uit vijf sectoren van 72°. Niet dat Poincaré opgelost is. Opnieuw een illustratie (~).
Deel 4 — De twaalf raadsels

Hier is de tabel. De indeling is een leesuitkomst van het kompas — een interpretatie (~-B), geen vastgesteld feit. Dat staat er expliciet bij, want de graad is geen wens.
#	Raadsel	Graad	Cirkel-lezing
3.1	Riemann	~-B	De kritieke lijn is een spiegelas (11 | 11).
3.2	P vs NP	~-B	De afstand tussen n² en 2ⁿ lijkt oneindig op de liniaal, maar is symmetrisch op de bol.
3.3	Poincaré	~-B	De singulariteit is een harde nul; de surgery is een roll-over (60 = 0).
3.4	Navier-Stokes	~-B	De divergentie (∇·u = 0) rolt om de nul heen; de vloeistof blijft glad.
3.5	Yang-Mills	~-B	Het massagat is een cyclische offset (1,0,0).
3.6	BSD	~-B	De rang is het aantal actieve assen.
3.7	Hodge	~-B	De algebraïsche cycli zijn gesloten lussen in de bol.
3.8	Fijnstructuur	~-B	137,035999... is geen muur; de rest rolt om via de operator (6).
3.9	Hiërarchie	~-B	10³² rolt om naar (3, 12, 0); de 12 is de spiegelas.
3.10	Zwart gat	~-B	De horizon is een gesloten bol.
3.11	Tijd	~-B	De pijl is een spiraal op een bol; de hittedood is de roll-over.
3.12	Horizon	~-B	De temperatuur is uniform over de bol.

Wat de graden betekenen. Elke lezing is ~-B: de vraag blijft, de route verandert, en de interpretatie is plausibel maar niet onafhankelijk getoetst. Geen enkele lezing is ✓-P, want geen enkele is bewezen. En geen enkele is ?-O, want er is wel een route.
De telling — van 7/3/2 naar 10/2/0

De vorige versie van dit document telde 7 cirkel, 3 liniaal en 2 beide. De liniaal-raadsels waren P vs NP, fijnstructuur en hiërarchie.

In de herziene lezing zijn die drie geen lineaire problemen meer. Ze zijn cyclisch. De liniaal was een misinterpretatie, geen eigenschap van het raadsel. Daarmee wordt de telling:

    10 cirkel (Poincaré, Navier-Stokes, Yang-Mills, Hodge, zwart gat, horizon, P vs NP, fijnstructuur, hiërarchie, tijd)

    2 beide (Riemann, BSD)

    0 puur liniaal

De gradering. 10/2/0 is de herziene leesuitkomst (~B). Het is een keuze, geen bewijs: de herindeling volgt uit het kompas, niet uit een onafhankelijke meting. De oude versie zei 7/3/2; de nieuwe zegt 10/2/0. Dat verschil is zelf ~-B. Wie de oude indeling verdedigt, heeft een punt zolang er geen onafhankelijke toets is die de nieuwe indeling bevestigt.

Daarom staat de herindeling ook als vierde falsificatiepunt in §5.2: als blijkt dat P vs NP, fijnstructuur en hiërarchie toch echt lineaire problemen zijn, moet de telling terug naar 7/3/2.
3.2 P vs NP — van liniaal naar cirkel

Het oude idee. P vs NP gaat over stappen (tijd, complexiteit). Geen rotatie. Liniaal.

Waarom dat niet klopt. De "astronomische kloof" tussen n² en 2ⁿ is een optische illusie. Op de liniaal lijkt de afstand oneindig. Op de bol is de afstand symmetrisch.

De berekening. Van 12 naar 6 is even ver als van 6 naar 12. De afstand is symmetrisch. En de Boolean-val (0² = 0, 1² = 1) is een lineair artefact.

Wat dit betekent. P en NP zijn dezelfde afstand. De kloof is geen echte kloof, maar de vervorming die optreedt als je een roterende bol platdrukt op een oneindige liniaal.

De graad. De observatie dat de afstand op een cirkel symmetrisch is, is ✓ (fenomeen). De conclusie dat P = NP is ~-B (interpretatie, niet getoetst). Of dit de fysieke werkelijkheid is, is ?-O.
Deel 5 — De eerlijkheidstoets

Dit document wil serieus genomen worden. Daarom zegt het precies wat het niet doet.

Wat dit document niet doet:

    Het lost de raadsels niet op. Dat is ?-O, werk voor een professor.

    Het claimt geen compleet bewijs.

    Het gebruikt geen termen die indruk maken maar niets meten.

Wat dit document wel doet:

    Het stelt één vraag: is base-60 het betere gereedschap voor ronde problemen?

    Het geeft per raadsel eerlijk de graad: ~-B, met de richting erbij.

    Het geeft per voorbeeld eerlijk aan: illustratie, geen afleiding.

    Het zegt precies wat het zou weerleggen.

Een document dat minder claimt, is moeilijker aan te vallen dan een document dat meer claimt. Dat is geen retoriek — dat is de regel van de Graad (§9): de graad is geen wens.
5.1 Het numerieke experiment met de fijnstructuur

De fijnstructuurconstante is een van de nauwkeurigst gemeten grootheden in de natuurkunde:
text

1/α ≈ 137,035999177

In base-10 is de rest (0,035999...) een decimaal die je moet afronden. In base-60 kun je hem opschrijven als een coördinaat. Laten we dat doen.

De eerste schaalstap (de 60-laag):
text

0,035999177 × 60 = 2,15995...

Dat zijn 2 hele stappen op de 60-schaal. De rest is 0,15995...

De tweede schaalstap (de 3600-laag):
text

0,15995... × 60 = 9,597...

Afgerond 9,6.

De roll-over via de operator:
text

9,6 × 6 = 57,6
57,6 = 0,8 × 72

En 72 is de rotatiesector (360/5).

Wat dit laat zien. De rest van 1/α laat zich netjes opdelen in base-60-schalen:
text

1/α = 137 + 2/60 + 9,6/3600

De 137 is de harde muur (de X-as). De 2 is de eerste deling (de kubus). En de 9,6 rolt via de operator om naar 57,6, wat 0,8 × 72 is.

De graad — en dit is belangrijk. Deze berekening is een rekenkundige identiteit. Ze is ✓ als fenomeen: de ontbinding klopt. Maar ze is geen falsificatie. Elke decimale rest laat zich door 60 en 6 heen en weer terugrekenen naar een veelvoud van 72 — dat is een eigenschap van de gekozen bewerking, niet een bewijs dat de fijnstructuur "cyclisch" is. De conclusie dat de fijnstructuur daarmee cyclisch is, is ~-B. De link naar de fysieke werkelijkheid is ?-O.

De eerdere versie van dit document zei hier "de toets is geslaagd, de brug is gebouwd". Dat was te sterk. Wat hier staat is een illustratie dat de base-60-notatie de rest netjes opdeelt — niet dat de fysica klopt. De Graad (§2) is daar duidelijk over: een ✓ verifieert het fenomeen, niet de interpretatie.
5.2 Wat dit zou weerleggen

Dit document is op vier punten falsifieerbaar:

    De indeling. Als blijkt dat de cirkel-raadsels helemaal niet cyclisch zijn, valt de these.

    De roll-over. Als blijkt dat de coördinaten niet omrollen via de operator (6), valt de brug.

    De grens. Als blijkt dat base-10 bij de cirkel-raadsels beter werkt dan base-60, valt de these omgekeerd.

    De herevaluatie. Als blijkt dat P vs NP, fijnstructuur en hiërarchie toch echt lineaire problemen zijn — zoals de vorige versie van dit document stelde — dan is de 10/2/0-telling te agressief en moet ze terug naar 7/3/2.

Punt 4 is er expliciet bijgezet omdat de sprong van 7/3/2 naar 10/2/0 zichtbaar moet blijven. Een lezer die de oude versie kent, moet kunnen zien wat er veranderd is en waarom.
Deel 6 — Conclusie

De twaalf grote raadsels in de wiskunde en natuurkunde zijn misschien geen wetten van de natuur. Het zijn mogelijk artefacten: constructiefouten die we zelf hebben veroorzaakt omdat we alles door een lineaire bril bekijken.

Maar dit document lost ze niet op. Het legt een route.

    Wij leggen geen nieuwe wiskunde. Wij leggen een route waar wiskundigen overheen kunnen lopen.

Vanuit een cyclische base-60-ruimte vallen de breuken zonder rommel op hun plek, en rollen de linialen om naar de spiegelas. De wiskunde klopt, de route is open, maar er is niets onafhankelijk getest.

De status is en blijft een eerlijke, open theorie die wacht op toetsing. ~-B, met de richting Open.
DEEL II — HET KOMPAS: DE ZEVEN MILLENIUMPROBLEMEN
Het kompas

De vijf functies geven samen een coördinaat in een driedimensionale ruimte:
text

1 = oorsprong (het punt van waaruit je telt)
2 = deler (de eerste deling: voor/achter, links/rechts)
3 = drie assen (X, Y, Z — de drie dimensies)
4 = vier hoeken (de vier kwadranten, de vier richtingen)
5 = stappen (de vijf sectoren van 72°)

Samen geven ze een coördinaat (x, y, z) in de bol (360°). En de bol klopt op twee manieren:
text

6 × 60 = 360 (stappen, lineair)
5 × 72 = 360 (rotatie, cyclisch)

Beide zijn waar. De ene is lineair, de andere cyclisch. Samen vertellen ze het verhaal van de bol.
1. Poincaré & Perelman — de opgeloste vraag
1.1 Het probleem

In 1904 stelde Henri Poincaré een vraag die honderd jaar onbeantwoord bleef: als je een driedimensionale ruimte hebt die gesloten is (geen rand) en enkelvoudig verbonden (elke lus kan worden samengeknepen tot een punt), is die ruimte dan altijd vervormbaar tot een 3-sfeer?

Met andere woorden: als een ruimte geen gaten heeft, is het dan altijd een bol? Poincaré vermoedde van wel, maar kon het niet bewijzen. Het werd een van de zeven millenniumprijsproblemen.

In 2003 publiceerde Grigori Perelman drie papers die het vermoeden bewezen. In 2010 erkende het Clay Mathematics Institute het bewijs. Poincaré's vraag is opgelost.
1.2 De formule
text

π₁(M) = 0  →  M ≅ S³

Perelman's gereedschap is de Ricci flow:
text

∂g/∂t = -2Rij

De metriek g stroomt in de tijd, gedreven door de Ricci-kromming Rij. Hobbelige ruimtes worden glad; gladde ruimtes blijven glad. Maar de stroming kan singulariteiten ontwikkelen: punten waar de kromming oneindig wordt en de vergelijking stopt.

Perelman's doorbraak was de surgery: stop bij de singulariteit, knip hem af, lijm een kap op het gat, en hervat de stroming.
1.3 De kompas-lezing

Het kompas geeft ons vijf functies: oorsprong (1), deler (2), drie assen (3), vier hoeken (4), vijf stappen (5). Samen geven ze een coördinaat (x, y, z) in de bol.

Lezen we Perelman's bewijs door het kompas, dan zien we twee dingen.

De singulariteit is een harde nul. Waar de kromming oneindig wordt (Rij → ∞), stopt de vergelijking. Je kunt er niet door delen en niet voorbij. In het kompas is dat een punt waar de coördinaat niet meer bestaat.

De surgery is een cyclische beweging. Perelman stopt bij de singulariteit, knipt hem af en hervat. Dat is een cyclische beweging: stop bij de nul, reset naar de oorsprong, begin een nieuwe ronde. In base-60 is dat 60 = 0 — je rolt om, je stopt niet bij een harde nul.

Het kompas leest Perelman's bewijs dus als een modulo-60-beweging: de singulariteit is de roll-over, de surgery is de reset, en de hervatting is de nieuwe ronde.
1.4 De formule voor het kompas
text

Rij → ∞  →  coördinaat (∞, 0, 0)
stop bij 60 (=0)  →  knip  →  hervat

Dat is een modulo-60-beweging: 60 mod 60 = 0. De surgery reset de coördinaat naar de oorsprong (0, 0, 0), en de hervatting begint een nieuwe ronde.
1.5 De vraag en de graad

Poincaré is opgelost. Perelman's bewijs is ✓. Maar het kompas stelt een vraag die Perelman niet stelde: is de singulariteit een harde nul of een cyclische nul?

Als de singulariteit een harde nul is (oneindig), dan is Perelman's surgery een noodoplossing: je moet knippen omdat de vergelijking stopt. Als de singulariteit een cyclische nul is (modulo-60), dan is de surgery natuurlijk: je rolt om, je stopt niet.

Graad: ~-B. De vraag blijft, de route verandert, en de interpretatie is plausibel maar niet onafhankelijk getoetst.
2. Navier-Stokes — de harde nul
2.1 Het probleem

De Navier-Stokes-vergelijkingen beschrijven hoe vloeistoffen stromen: water, lucht, bloed, alles wat vloeit. Ze zijn al sinds de negentiende eeuw bekend en werken in de praktijk (weersvoorspelling, vliegtuigontwerp, klimaatmodellen). Maar de wiskundige vraag is onopgelost: bestaan er altijd gladde oplossingen in drie dimensies, of kunnen er singulariteiten ontstaan — punten waar de snelheid oneindig wordt?

Het probleem staat sinds 1934 open en is een van de zeven millenniumprijsproblemen.
2.2 De formule
text

∂u/∂t + (u · ∇)u = -∇p/ρ + ν∇²u
∇ · u = 0

De eerste regel is de impulsvergelijking: de snelheid u verandert in de tijd door advectie, druk en viscositeit. De tweede regel is de incompressibiliteit: de divergentie van u is nul.

Die tweede regel is de kern. ∇ · u = 0 is een harde voorwaarde. Het vectorveld moet exact divergentievrij zijn. Er is geen "bijna nul" — het is nul, of het is geen oplossing.
2.3 De kompas-lezing

Lezen we Navier-Stokes door het kompas, dan zien we dezelfde structuur als bij Perelman.

De divergentie is een harde nul. ∇ · u = 0 is een punt waar de vergelijking stopt als je er doorheen wilt delen. In het kompas is dat een punt waar de coördinaat niet meer bestaat — net als de singulariteit bij Ricci flow.

Het kompas leest die nul als cyclisch. In base-60 is 60 = 0: je rolt om, je stopt niet bij een harde nul. Dus de divergentie ∇ · u = 0 wordt een roll-over: de stroom gaat niet richting een harde nul, maar om de nul heen. De vloeistof blijft vloeibaar.

Dat is dezelfde beweging als Perelman's surgery: stop bij de nul, reset, hervat. Alleen is het bij Navier-Stokes geen knip maar een rol — de stroom rolt om de nul heen in plaats van er tegenaan te botsen.
2.4 De formule voor het kompas
text

∇ · u = 0  →  coördinaat (0, 0, 0)
stop bij 60 (=0)  →  rol om  →  hervat

Dat is dezelfde modulo-60-beweging als bij Perelman: de stroom rolt om de nul heen, en de vloeistof blijft glad.
2.5 De vraag en de graad

Navier-Stokes is onopgelost. Maar het kompas stelt een vraag: is de divergentie een harde nul of een cyclische nul?

Als de divergentie een harde nul is (∇ · u = 0, exact), dan is de vloeistof gedwongen om exact divergentievrij te zijn, en dat kan singulariteiten veroorzaken. Als de divergentie een cyclische nul is (modulo-60), dan rolt de stroom om de nul heen, en blijven de oplossingen glad.

Graad: ~-B. De vraag blijft, de route verandert, de interpretatie is plausibel maar niet bevestigd.
3. Yang-Mills — het massagat
3.1 Het probleem

De Yang-Mills-theorie beschrijft de zwakke kernkracht en de sterke kernkracht. Ze is de ruggengraat van het Standaardmodel. Maar er is een wiskundige vraag die sinds 1954 openstaat: bestaat er een massagat? Met andere woorden: is de massa van de zwakke kernkracht groter dan nul, of kan ze nul zijn?

Het probleem is een van de zeven millenniumprijsproblemen.
3.2 De formule
text

L = -1/4 F^a_μν F^{aμν}

De veldsterkte F^a_μν beschrijft de kracht. De vraag is of de theorie een massagat heeft: een minimale massa die niet nul is.
3.3 De kompas-lezing

Lezen we Yang-Mills door het kompas, dan zien we een sprong in de coördinaat.

Het massagat is een sprong. De massa is niet nul, maar groter dan nul. In het kompas is dat een sprong: de coördinaat begint niet bij (0,0,0), maar bij een minimum. De oorsprong is niet bereikbaar.

Het kompas leest die sprong als een cyclische offset. In base-60 is 60 = 0, maar de tussenliggende waarden zijn bereikbaar. Het massagat is een offset: de coördinaat begint bij een minimum (bijvoorbeeld (1,0,0)), niet bij de oorsprong. De theorie "mist" de oorsprong, maar heeft wel een minimum.
3.4 De formule voor het kompas
text

massa > 0  →  coördinaat (1, 0, 0)
start bij 1  →  geen oorsprong  →  massagat

Het kompas leest het massagat als een offset: de theorie begint niet bij nul, maar bij een minimum.
3.5 De vraag en de graad

Yang-Mills is onopgelost. Maar het kompas stelt een vraag: is het massagat een offset (minimum > 0) of een echte nul (massa = 0)?

Graad: ~-B. De vraag blijft, de route verandert, de interpretatie is plausibel maar niet bevestigd.
4. Riemann — de spiegelas
4.1 Het probleem

De Riemann-hypothese gaat over de zeta-functie en de priemgetallen. Ze stelt dat alle niet-triviale nulpunten van de zeta-functie op de kritieke lijn Re(s) = 1/2 liggen. Onbewezen sinds 1859. Een van de zeven millenniumprijsproblemen.
4.2 De formule
text

ζ(s) = 1 + 1/2^s + 1/3^s + 1/4^s + ...

De nulpunten van deze functie liggen op Re(s) = 1/2.
4.3 De kompas-lezing

Lezen we Riemann door het kompas, dan zien we een spiegelas.

De kritieke lijn is een spiegelas. Re(s) = 1/2 is de helft van de reële as. In het kompas is dat een spiegelas: 11 | 11. Aan beide kanten van de as staat een gelijk deel.

Het kompas leest de kritieke lijn als de spiegelas van het register. De as is geen leegte, maar het observatiepunt van waaruit je telt. De nulpunten liggen aan beide kanten van de as, en de as is de spiegel.
4.4 De formule voor het kompas
text

Re(s) = 1/2  →  spiegelas 11 | 11
nulpunten  →  aan beide kanten van de as

Het kompas leest de nulpunten als spiegels van elkaar: elk nulpunt aan de ene kant heeft een spiegelbeeld aan de andere kant.
4.5 De vraag en de graad

Riemann is onopgelost. Maar het kompas stelt een vraag: is de kritieke lijn een spiegelas (11 | 11) of een harde grens (1/2)?

Graad: ~-B. De vraag blijft, de route verandert, de interpretatie is plausibel maar niet bevestigd.
5. Hodge — de gesloten lussen
5.1 Het probleem

De Hodge-conjectuur gaat over de topologie van algebraïsche variëteiten. Ze stelt dat elke Hodge-klasse een lineaire combinatie is van algebraïsche cycli. Onbewezen sinds 1950. Een van de zeven millenniumprijsproblemen.
5.2 De formule
text

H^{2k}(X, Q) ∩ H^{k,k}(X) = algebraïsche cycli

De Hodge-klassen zijn de topologische klassen; de algebraïsche cycli zijn de meetkundige lussen. De vraag is of ze samenvallen.
5.3 De kompas-lezing

Lezen we Hodge door het kompas, dan zien we gesloten lussen.

De algebraïsche cycli zijn gesloten lussen. Een algebraïsche cyclus is een gesloten lus in de variëteit. In het kompas is dat een gesloten pad in de bol: je begint bij de oorsprong, je gaat rond, en je komt terug.

Het kompas leest de Hodge-klassen als de lussen zelf. De Hodge-klassen zijn de topologische beschrijving van de lussen. Het kompas leest ze als dezelfde lussen, maar dan in coördinaten.
5.4 De formule voor het kompas
text

algebraïsche cyclus  →  gesloten lus in de bol
Hodge-klasse  →  dezelfde lus, topologisch beschreven

Het kompas leest de Hodge-klasse als dezelfde lus, maar dan als coördinaat.
5.5 De vraag en de graad

Hodge is onopgelost. Maar het kompas stelt een vraag: zijn de Hodge-klassen dezelfde lussen als de algebraïsche cycli, of zijn het verschillende lussen?

Graad: ~-B. De vraag blijft, de route verandert, de interpretatie is plausibel maar niet bevestigd.
6. Birch and Swinnerton-Dyer — de actieve assen
6.1 Het probleem

De Birch and Swinnerton-Dyer-conjectuur gaat over elliptische krommen. Ze stelt dat de rang van een elliptische kromme gelijk is aan de orde van de nul van de bijbehorende L-functie bij s = 1. Onbewezen sinds 1965. Een van de zeven millenniumprijsproblemen.
6.2 De formule
text

ord_{s=1} L(E, s) = rank(E(Q))

De rang is het aantal onafhankelijke punten op de kromme. De L-functie beschrijft de kromme als een reeks.
6.3 De kompas-lezing

Lezen we BSD door het kompas, dan zien we actieve assen.

De rang is het aantal actieve assen. Een elliptische kromme heeft een rang: het aantal onafhankelijke punten. In het kompas is dat het aantal actieve assen: hoeveel assen (X, Y, Z) doen mee?

Het kompas leest de L-functie als de som van de assen. De L-functie beschrijft de kromme als een reeks. Het kompas leest die reeks als de som van de actieve assen.
6.4 De formule voor het kompas
text

rank(E(Q)) = aantal actieve assen
L(E, s) = som van de actieve assen

Het kompas leest de L-functie als de som van de assen.
6.5 De vraag en de graad

BSD is onopgelost. Maar het kompas stelt een vraag: is de rang het aantal actieve assen (1, 2, 3) of een continue waarde?

Graad: ~-B. De vraag blijft, de route verandert, de interpretatie is plausibel maar niet bevestigd.
7. P vs NP — dezelfde afstand

(Zie §3.2 in Deel I voor de uitgebreide versie. Hier de kern.)
7.1 Het probleem

P vs NP gaat over computers. P is de klasse van problemen die snel opgelost kunnen worden. NP is de klasse van problemen waarvan een oplossing snel gecontroleerd kan worden. De vraag is of P = NP: kan elk probleem dat snel gecontroleerd kan worden, ook snel opgelost worden?

Onbewezen sinds 1971. Een van de zeven millenniumprijsproblemen.
7.2 De formule
text

P = NP?

7.3 De kompas-lezing

Lezen we P vs NP door het kompas, dan zien we dezelfde afstand.

Vinden en controleren zijn dezelfde afstand. In het kompas is de afstand tussen twee punten dezelfde, of je nu van A naar B gaat (vinden) of van B naar A (controleren). De afstand is symmetrisch.
7.4 De formule voor het kompas
text

P = afstand van A naar B
NP = afstand van B naar A

7.5 De vraag en de graad

P vs NP is onopgelost. Maar het kompas stelt een vraag: is de afstand symmetrisch (P = NP) of asymmetrisch (P ≠ NP)?

Graad: ~-B. De vraag blijft, de route verandert, de interpretatie is plausibel maar niet bevestigd.
Conclusie (Deel II)

De zeven millenniumproblemen zijn misschien geen wetten van de natuur. Het zijn mogelijk artefacten: constructiefouten die we zelf hebben veroorzaakt omdat we alles door een lineaire base-10-bril bekijken.

Lezen we de problemen door het kompas — de vijf functies, de bol, de cyclische nul — dan vallen ze op hun plek. De harde nullen worden cyclische nullen. De spiegelas wordt een observatiepunt. De lussen worden coördinaten. De rang wordt een aantal actieve assen. De afstand wordt symmetrisch.

Dit is een theorie. De wiskunde klopt, de route is open, maar er is niets onafhankelijk getest. De status is en blijft een eerlijke, open theorie die wacht op toetsing.
DEEL III — DE VIJF AANVULLENDE RAADSELS (3.8–3.12)
3.8 Fijnstructuur — van muur naar roll-over

Het oude idee. 137 is een harde muur. Een punt op de X-as: (137, 0, 0). Base-10 is genoeg.

Waarom dat niet klopt. De rest (0,035999...) is geen rommel. Het is een getal dat je kunt opschrijven in base-60. En als je dat doet, gebeurt er iets.

De berekening.

    0,035999177 × 60 = 2,15995... → 2 hele stappen (de 2 is de deler/kubus).

    0,15995... × 60 = 9,597... → afgerond 9,6.

    En dan de operator: 9,6 × 6 = 57,6.

    En 57,6 = 0,8 × 72°.

Wat dit betekent. De fijnstructuur is geen muur. Het is een stapeling van base-60-schalen:
text

1/α = 137 + 2/60 + 9,6/3600

De 137 is de harde muur (de X-as). De 2 is de eerste deling (de kubus). En de 9,6 rolt via de operator om naar 57,6, wat exact 0,8 × 72° is. De "broken decimal" verdwijnt.

De graad. ~-B. Want de rekenkunde is ✓ (het klopt). Maar de conclusie dat de fysica daarmee "cyclisch" is, is ?-O. Je hebt laten zien dat de notatie werkt, niet dat de werkelijkheid zo is.
3.9 Hiërarchie — van kloof naar coördinaat

Het oude idee. 10³² is een onvoorstelbare lineaire kloof. Geen rotatie. Liniaal.

Waarom dat niet klopt. Omdat je de kloof door de operator kunt halen. En dan klapt hij in elkaar.

De berekening.

    Basis: 10 × 6 = 60. En 60 mod 60 = 0. (De lineaire basis klapt weg).

    Exponent: 32 × 6 = 192. En 192 / 60 = 3 met een rest van 12.

Wat dit betekent. De kloof van 10³² rolt om naar de coördinaat (3, 12, 0). En 12 is exact de helft van de 24-uurcyclus (de spiegelas). De astronomische kloof klapt in elkaar tot een symmetrische coördinaat.
text

10³² → (3, 12, 0)
12 = spiegelas (helft van 24)

De graad. ~-B. Want de rekenkunde is ✓ (192/60 = 3 rest 12). Maar of dit de fysieke werkelijkheid is, is ?-O.
3.10 Zwart gat — de horizon

Het probleem. Gaat informatie verloren wanneer een zwart gat verdampt? Dit is de informatieparadox van Hawking. Onopgelost sinds 1976.

De formule.
text

S_BH = A / (4ℓ_P²)

De entropie van een zwart gat is evenredig met de oppervlakte van de horizon.

De kompas-lezing. De horizon is een bol. De oppervlakte A is de oppervlakte van een bol. In het kompas is dat een gesloten oppervlak — een bol met straal r. De entropie is de oppervlakte van die bol. En dat is precies wat een cirkelprobleem is: rotatie, bol, cyclisch.

De formule voor het kompas.
text

S_BH = A / (4ℓ_P²) → A = 4πr²
Een gesloten bol. Rotatie.

De vraag en de graad. Het zwarte gat is een cirkelprobleem; base-60 is hier mogelijk beter, want de horizon is een bol. Graad: ~-B. De interpretatie is plausibel maar niet bevestigd.
3.11 Tijd — de pijl

Het probleem. Waarom is er een richting in de tijd? De meeste fundamentele natuurwetten zijn tijdsymmetrisch, maar de werkelijkheid is dat niet. Onopgelost.

De formule.
text

dS/dt ≥ 0

De tweede wet van de thermodynamica: de entropie neemt altijd toe.

De kompas-lezing. De pijl van de tijd is een richting. De tijd gaat vooruit, nooit achteruit. In het kompas is dat een richting in de bol — een pad dat van (0,0,0) naar (x,y,z) gaat en niet terug. In de herziene lezing is dat een spiraal op een bol: je gaat vooruit én je rolt om. De hittedood is de roll-over.

De formule voor het kompas.
text

dS/dt ≥ 0 → een spiraal op de bol
De hittedood = de roll-over (60 = 0)

De vraag en de graad. De tijd is een cirkelprobleem; base-60 is hier mogelijk beter, want de pijl van de tijd is een richting in een cyclus. Graad: ~-B.
3.12 Horizon — de uniforme temperatuur

Het probleem. Waarom is de temperatuur van de kosmische achtergrondstraling aan alle kanten exact gelijk, terwijl die gebieden nooit contact hebben gehad? Dit is het horizonprobleem. Onopgelost sinds 1969.

De formule.
text

T = 2,725 K (universeel)

De kompas-lezing. De temperatuur is uniform. Overal hetzelfde. In het kompas is dat een bol waar alle punten dezelfde waarde hebben — een constante op de bol. En dat is precies wat een cirkelprobleem is: rotatie, bol, cyclisch.

De formule voor het kompas.
text

T = 2,725 K → uniforme bol
Alle punten hebben dezelfde waarde.

De vraag en de graad. De horizon is een cirkelprobleem; base-60 is hier mogelijk beter, want de temperatuur is uniform over een bol. Graad: ~-B.

EINDE
