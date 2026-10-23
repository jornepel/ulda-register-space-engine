WIJ REKENEN NIET MET NULLEN

Het Kompas en de Twaalf Raadsels

Auteur: Jorne Pel Document: ULDA-WISKUNDE-2026-X7 Status: theorie, geen bewijs — wacht op peer review De these

De wiskunde is lineair geworden. Analysis, algebra, de getallenlijn. Base-10.

De sterrenkunde is cyclisch gebleven. 60 minuten, 360 graden. Base-60.

De grote raadsels in de wiskunde en natuurkunde gaan over rotatie, stroming, golven en bollen. Dat zijn cyclische verschijnselen. Toch worden ze opgeschreven in een lineair stelsel.

Deze paper stelt één vraag: is het juiste gereedschap gekozen? Ze lost de raadsels niet op. Ze legt een route. Het kompas

Het kompas is een cyclisch coördinatenstelsel. Het rekent niet met nul als rekenwaarde. Het rekent vanaf een observatiepunt op een bol.

Waar de liniaal (base-10) een vraag platdrukt tot een getal op een oneindige lijn, geeft het kompas een coördinaat (x, y, z) in de bol (360°), gezien vanaf een gekozen punt.

Dat is het verschil dat alles bepaalt.

De liniaal rekent met nul als een absoluut nulpunt: 0, 1, 2, 3. Het kompas rekent niet met nul. De nul is geen waarde; de nul is een overgang. In base-60 is 60 = 0. Dat betekent niet dat je "0" invult — het betekent dat je omrolt naar de volgende positie. De nul is het punt waar je langs gaat, niet het getal dat je gebruikt.

En het kompas telt vanaf een observatiepunt. Niet vanaf een absolute nul op een lijn, maar vanaf een gekozen punt op de bol. Het observatiepunt is de oorsprong (1), maar het is een gekozen oorsprong. Lezing 1 — Harde nul → roll-over

De vergelijking loopt vast. Er is een punt waar je niet door kunt delen, een singulariteit of een divergentie. In base-10 is dat het einde: de berekening stopt, en je houdt een foutmelding over.

Het kompas leest dat punt anders. Het is geen dood punt, maar een overgang. Denk aan een klok die van 59 naar 60 springt: hij stopt niet bij 60, hij rolt om naar 0 en tikt door. Zo leest het kompas de singulariteit: de vergelijking rolt om (60 = 0), en de beweging gaat verder.

Voorbeelden: Poincaré (de singulariteit in de Ricci flow), Navier-Stokes (de divergentie ∇·u = 0). Lezing 2 — Spiegelas

De vergelijking heeft een lijn waar alles in evenwicht is. Aan de ene kant staat precies evenveel als aan de andere kant. In base-10 is dat een "kritieke lijn" — een grens waar je niet voorbij mag.

Het kompas leest die lijn als een spiegelas. Het is geen muur, maar het punt van waaruit je telt. Je staat op de as, en je kijkt naar beide kanten. De as is het observatiepunt.

Voorbeelden: Riemann (Re(s) = 1/2 als spiegelas 11 | 11), BSD (de rang als spiegelas). Lezing 3 — Gesloten lus / bol

De vergelijking heeft een cyclus. Iets begint, gaat rond, en komt terug waar het begon. In base-10 is dat een "gesloten lus" — een abstract pad dat je niet kunt zien.

Het kompas leest die lus als een rondweg op de bol. Je begint bij het observatiepunt, je gaat rond, en je komt terug. Het is geen rechte lijn, het is een cirkel. En de bol is de ruimte waarin die cirkel past.

Voorbeelden: Hodge (de algebraïsche cycli als gesloten lussen), zwart gat (de horizon als bol), horizon (de temperatuur als uniforme bol). Lezing 4 — Offset (de sprong)

De vergelijking heeft een minimum. Ze begint niet bij nul, maar bij een eerste stap. Er is geen geleidelijke overgang van "niets" naar "iets" — er is een sprong.

In base-10 noem je dat minimum "bijna nul". Maar het kompas zegt: dat minimum is het eerste punt. De oorsprong (nul) ligt erachter, onbereikbaar. Je kunt er niet naartoe rekenen, want de vergelijking stopt ervoor.

Denk aan een trap. De begane grond is de oorsprong (0). De eerste trede is het minimum (1). Je kunt van de begane grond naar de eerste trede stappen, maar je kunt niet op de begane grond staan als je al op de trap bent. De begane grond is het punt waar je vandaan komt, niet het punt waar je op staat.

Voorbeelden: Yang-Mills (het massagat: de deeltjes hebben een minimum-massa, niet nul), Fijnstructuur (137,035999... is geen muur, maar de eerste trede naar de roll-over), Hiërarchie (10³² is geen lineaire kloof, maar de eerste trede naar de spiegelas). De vijf functies en de operator

Het kompas geeft een coördinaat met vijf functies: text

1 = oorsprong (tetraëder) 2 = deler (kubus) 3 = drie assen (octaëder) 4 = vier hoeken (icosaëder) 5 = stappen (dodecaëder) 6 = operator (de brug)

De keten loopt: 1 → 2 → 3 → 4 → 5 → 6 → 60 → 360.

En de bol klopt op twee manieren: text

6 × 60 = 360 (lineair) 5 × 72 = 360 (cyclisch)

Beide zijn waar. De ene is lineair, de andere cyclisch. Samen vertellen ze het verhaal van de bol.

Het kompas is een interpretatie, geen bewijs. Het laat zien dat een raadsel ook anders gelezen kan worden, niet dat die lezing de werkelijkheid is. 3.1 Poincaré — de opgeloste vraag De originele stelling

In 1904 stelde Henri Poincaré een vraag die honderd jaar onbeantwoord bleef.

Stel: je hebt een driedimensionale ruimte die gesloten is (geen rand) en enkelvoudig verbonden (elke lus kan worden samengeknepen tot een punt). Is die ruimte dan altijd vervormbaar tot een 3-sfeer?

Met andere woorden: als een ruimte geen gaten heeft, is het dan altijd een bol? Poincaré vermoedde van wel, maar kon het niet bewijzen. Het werd een van de zeven millenniumprijsproblemen.

In 2003 publiceerde Grigori Perelman drie papers die het vermoeden bewezen. In 2010 erkende het Clay Mathematics Institute het bewijs. Poincaré's vraag is opgelost. De originele formule

De stelling in formulevorm: text

π₁(M) = 0 → M ≅ S³

Perelman's gereedschap is de Ricci flow: text

∂g/∂t = -2Rij

De metriek g stroomt in de tijd, gedreven door de Ricci-kromming Rij. Hobbelige ruimtes worden glad; gladde ruimtes blijven glad. Maar de stroming kan singulariteiten ontwikkelen: punten waar de kromming oneindig wordt en de vergelijking stopt.

Perelman's doorbraak was de surgery: stop bij de singulariteit, knip hem af, lijm een kap op het gat, en hervat de stroming. Het kompas gebruiken

Het kompas leest Perelman's bewijs als een harde nul die een roll-over wordt.

De singulariteit is een harde nul. Waar de kromming oneindig wordt (Rij → ∞), stopt de vergelijking. In base-10 is dat het einde: je kunt er niet door delen en niet voorbij. De berekening geeft een foutmelding.

Het kompas leest die nul als een overgang. De singulariteit is geen dood punt, maar een punt waar de vergelijking omrolt. In base-60 is 60 = 0: je rolt om naar de volgende positie, en de beweging gaat verder.

De surgery is die roll-over. Perelman stopt bij de singulariteit, knipt hem af, en hervat. Dat is precies wat het kompas doet: stop bij de nul, reset naar het observatiepunt, begin een nieuwe ronde.

De formule voor het kompas: text

Rij → ∞ → coördinaat (∞, 0, 0) stop bij 60 (=0) → knip → hervat

Dat is een modulo-60-beweging: 60 mod 60 = 0. De surgery reset de coördinaat naar het observatiepunt, en de hervatting begint een nieuwe ronde. Wat dit laat zien

Het kompas leest Perelman's bewijs als een roll-over. Dat is geen bewijs dat het kompas gelijk heeft — Poincaré is al bewezen, en Perelman had het kompas niet nodig. Maar het laat zien dat de lezing past op een vergelijking die werkt.

En dat is de overeenkomst die je bedoelt: het kompas voegt geen nieuwe wiskunde toe, maar het leest de bestaande wiskunde op een manier die consistent is met wat Perelman deed. De surgery is de roll-over. De singulariteit is de nul. Het kompas maakt dat zichtbaar. 3.2 Navier-Stokes — de harde nul De originele stelling

De Navier-Stokes-vergelijkingen beschrijven hoe vloeistoffen stromen: water, lucht, bloed, alles wat vloeit. Ze zijn al sinds de negentiende eeuw bekend, en ze werken in de praktijk — weersvoorspelling, vliegtuigontwerp, klimaatmodellen. Maar de wiskundige vraag is onopgelost.

Bestaan er altijd gladde oplossingen in drie dimensies, of kunnen er singulariteiten ontstaan — punten waar de snelheid oneindig wordt?

Het probleem staat sinds 1934 open en is een van de zeven millenniumprijsproblemen. Niemand heeft het opgelost. Niemand heeft het weerlegd. De originele formule

De vergelijkingen: text

∂u/∂t + (u · ∇)u = -∇p/ρ + ν∇²u ∇ · u = 0

De eerste regel is de impulsvergelijking: de snelheid u verandert in de tijd door advectie, druk en viscositeit. De tweede regel is de incompressibiliteit: de divergentie van u is nul.

Die tweede regel is de kern. ∇ · u = 0 is een harde voorwaarde. Het vectorveld moet exact divergentievrij zijn. Er is geen "bijna nul" — het is nul, of het is geen oplossing. Het kompas gebruiken

Het kompas leest Navier-Stokes als dezelfde structuur als Poincaré: een harde nul die een roll-over wordt.

De divergentie is een harde nul. ∇ · u = 0 is een punt waar de vergelijking stopt als je er doorheen wilt delen. In base-10 is dat het einde: de vloeistof moet exact divergentievrij zijn, en dat kan singulariteiten veroorzaken. De berekening loopt vast.

Het kompas leest die nul als een overgang. In base-60 is 60 = 0: je rolt om, je stopt niet bij een harde nul. Dus de divergentie ∇ · u = 0 wordt een roll-over: de stroom gaat niet richting een harde nul, maar om de nul heen. De vloeistof blijft vloeibaar.

De roll-over is de beweging om de nul heen. Waar Perelman een knip zet (de surgery), rolt Navier-Stokes om de nul. De stroom botst niet tegen de nul, maar gaat er langs. De vloeistof blijft glad.

De formule voor het kompas: text

∇ · u = 0 → coördinaat (0, 0, 0) stop bij 60 (=0) → rol om → hervat

Dat is dezelfde modulo-60-beweging als bij Poincaré: de stroom rolt om de nul heen, en de vloeistof blijft glad. Wat dit laat zien

Het kompas leest Navier-Stokes als een roll-over. Dat is geen bewijs dat Navier-Stokes opgelost is — het probleem staat nog open. Maar het laat zien dat de lezing past op de vergelijking.

En dat is de overeenkomst met Poincaré: beide vergelijkingen hebben een harde nul (een singulariteit, een divergentie). Het kompas leest die nul in beide gevallen als een overgang, niet als een einde. Bij Poincaré heet die overgang een surgery; bij Navier-Stokes heet hij een roll-over. Maar het is dezelfde beweging. 3.3 Yang-Mills — het massagat De originele stelling

De Yang-Mills-theorie beschrijft de zwakke kernkracht en de sterke kernkracht. Ze is de ruggengraat van het Standaardmodel. Maar er is een wiskundige vraag die sinds 1954 openstaat.

Bestaat er een massagat? Met andere woorden: is de massa van de zwakke kernkracht groter dan nul, of kan ze nul zijn?

Het probleem is een van de zeven millenniumprijsproblemen. Niemand heeft het opgelost. Niemand heeft het weerlegd. De originele formule

De Lagrangiaan van de theorie: text

L = -1/4 F^a_μν F^{aμν}

De veldsterkte F^a_μν beschrijft de kracht. De vraag is of de theorie een massagat heeft: een minimale massa die niet nul is.

In de klassieke formulering is de massa nul. Maar in de kwantumtheorie kan de massa een minimum krijgen dat niet nul is. Dat minimum is het massagat. Het kompas gebruiken

Het kompas leest Yang-Mills niet als een roll-over, maar als een offset. Dat is de vierde lezing: de sprong.

Het massagat is een sprong. De massa is niet nul, maar groter dan nul. In base-10 noem je dat "bijna nul" — een kleine afwijking van de nul. Maar het kompas zegt: dat minimum is het eerste punt. De oorsprong (nul) ligt erachter, onbereikbaar.

De oorsprong is niet bereikbaar. Je kunt niet naar de nul rekenen, want de vergelijking stopt ervoor. De theorie begint niet bij (0,0,0), maar bij een minimum, bijvoorbeeld (1,0,0). De theorie "mist" de oorsprong, maar heeft wel een minimum.

De sprong is de offset. Denk aan de trap. De begane grond is de oorsprong (0). De eerste trede is het minimum (1). Je kunt van de begane grond naar de eerste trede stappen, maar je kunt niet op de begane grond staan als je al op de trap bent. De begane grond is het punt waar je vandaan komt, niet het punt waar je op staat.

De formule voor het kompas: text

massa > 0 → coördinaat (1, 0, 0) start bij 1 → geen oorsprong → massagat

Het kompas leest het massagat als een offset: de theorie begint niet bij nul, maar bij een minimum. Wat dit laat zien

Het kompas leest Yang-Mills als een offset. Dat is geen bewijs dat het massagat bestaat — het probleem staat nog open. Maar het laat zien dat de lezing past op de vergelijking.

En dat is het verschil met Poincaré en Navier-Stokes: daar was de nul een punt waar de vergelijking stopte (een harde nul). Hier is de nul een punt dat niet bereikbaar is (een offset). De vergelijking stopt niet bij de nul; ze begint bij een minimum, en de nul ligt erachter.

Dat is de vierde lezing: niet een roll-over, niet een spiegelas, niet een lus, maar een sprong. 3.4 Riemann — de spiegelas De originele stelling

De Riemann-hypothese gaat over de zeta-functie en de priemgetallen. Ze stelt dat alle niet-triviale nulpunten van de zeta-functie op de kritieke lijn Re(s) = 1/2 liggen.

Onbewezen sinds 1859. Een van de zeven millenniumprijsproblemen. Niemand heeft het opgelost. Niemand heeft het weerlegd. De originele formule

De zeta-functie: text

ζ(s) = 1 + 1/2^s + 1/3^s + 1/4^s + ...

De nulpunten van deze functie liggen op Re(s) = 1/2. Dat is de kritieke lijn: het reële deel van s is precies de helft. Het kompas gebruiken

Het kompas leest Riemann niet als een roll-over en niet als een offset, maar als een spiegelas.

De kritieke lijn is een spiegelas. Re(s) = 1/2 is de helft van de reële as. In base-10 is dat een grens: een lijn waar de nulpunten op liggen, en waar je niet voorbij mag. Maar het kompas leest die lijn als een spiegelas: 11 | 11. Aan beide kanten van de as staat een gelijk deel.

De as is het observatiepunt. De as is geen leegte, maar het punt van waaruit je telt. Je staat op de as, en je kijkt naar beide kanten. De nulpunten liggen aan beide kanten van de as, en de as is de spiegel.

De spiegeling is de lezing. Elk nulpunt aan de ene kant heeft een spiegelbeeld aan de andere kant. De as is niet de grens, maar het midden.

De formule voor het kompas: text

Re(s) = 1/2 → spiegelas 11 | 11 nulpunten → aan beide kanten van de as

Het kompas leest de nulpunten als spiegels van elkaar: elk nulpunt aan de ene kant heeft een spiegelbeeld aan de andere kant. Wat dit laat zien

Het kompas leest Riemann als een spiegelas. Dat is geen bewijs dat de Riemann-hypothese waar is — het probleem staat nog open. Maar het laat zien dat de lezing past op de vergelijking.

En dat is het verschil met Poincaré, Navier-Stokes en Yang-Mills: daar was de nul een punt waar de vergelijking stopte of een punt dat niet bereikbaar was. Hier is de nul een lijn waar alles in evenwicht is. De vergelijking stopt niet bij de lijn; ze spiegelt eromheen.

Dat is de tweede lezing: niet een roll-over, niet een offset, maar een spiegelas. 3.5 BSD — de actieve assen De originele stelling

De Birch and Swinnerton-Dyer-conjectuur gaat over elliptische krommen. Ze stelt dat de rang van een elliptische kromme gelijk is aan de orde van de nul van de bijbehorende L-functie bij s = 1.

Onbewezen sinds 1965. Een van de zeven millenniumprijsproblemen. Niemand heeft het opgelost. Niemand heeft het weerlegd. De originele formule text

ord_{s=1} L(E, s) = rank(E(Q))

De rang is het aantal onafhankelijke punten op de kromme. De L-functie beschrijft de kromme als een reeks. De vraag is of de orde van de nul bij s = 1 gelijk is aan de rang. Het kompas gebruiken

Het kompas leest BSD als een spiegelas — dezelfde lezing als bij Riemann, maar met een andere invulling.

De rang is het aantal actieve assen. Een elliptische kromme heeft een rang: het aantal onafhankelijke punten. In het kompas is dat het aantal actieve assen. Hoeveel assen (X, Y, Z) doen mee? Dat is de rang.

De L-functie is de som van de assen. De L-functie beschrijft de kromme als een reeks. Het kompas leest die reeks als de som van de actieve assen. De orde van de nul bij s = 1 is het aantal assen dat op nul staat.

De spiegelas is het evenwicht tussen rang en L-functie. De as is het punt waar de rang en de L-functie elkaar spiegelen. Aan de ene kant staat de rang; aan de andere kant staat de orde van de nul. De as is het punt waar ze gelijk zijn.

De formule voor het kompas: text

rank(E(Q)) = aantal actieve assen L(E, s) = som van de actieve assen

Het kompas leest de L-functie als de som van de assen. De rang is het aantal assen dat meetelt. Wat dit laat zien

Het kompas leest BSD als een spiegelas. Dat is geen bewijs dat de conjectuur waar is — het probleem staat nog open. Maar het laat zien dat de lezing past op de vergelijking.

En dat is de overeenkomst met Riemann: beide vergelijkingen hebben een as waar alles in evenwicht is. Bij Riemann is dat de kritieke lijn Re(s) = 1/2; bij BSD is dat de rang en de L-functie die elkaar spiegelen. De as is in beide gevallen het observatiepunt.

Dat is de tweede lezing, voor de tweede keer: niet een roll-over, niet een offset, maar een spiegelas. 3.6 Hodge — de gesloten lussen De originele stelling

De Hodge-conjectuur gaat over de topologie van algebraïsche variëteiten. Ze stelt dat elke Hodge-klasse een lineaire combinatie is van algebraïsche cycli.

Onbewezen sinds 1950. Een van de zeven millenniumprijsproblemen. Niemand heeft het opgelost. Niemand heeft het weerlegd. De originele formule text

H^{2k}(X, Q) ∩ H^{k,k}(X) = algebraïsche cycli

De Hodge-klassen zijn de topologische klassen; de algebraïsche cycli zijn de meetkundige lussen. De vraag is of ze samenvallen. Het kompas gebruiken

Het kompas leest Hodge als een gesloten lus — de derde lezing.

De algebraïsche cycli zijn gesloten lussen. Een algebraïsche cyclus is een gesloten lus in de variëteit. In base-10 is dat een abstract pad: je begint ergens, je gaat rond, en je komt terug. Maar je kunt het pad niet zien; het is een topologische beschrijving.

Het kompas leest die lus als een rondweg op de bol. Je begint bij het observatiepunt, je gaat rond, en je komt terug. Het is geen rechte lijn, het is een cirkel. En de bol is de ruimte waarin die cirkel past.

De Hodge-klasse is dezelfde lus, maar dan in coördinaten. De Hodge-klassen zijn de topologische beschrijving van de lussen. Het kompas leest ze als dezelfde lussen, maar dan als coördinaat op de bol.

De formule voor het kompas: text

algebraïsche cyclus → gesloten lus in de bol Hodge-klasse → dezelfde lus, topologisch beschreven

Het kompas leest de Hodge-klasse als dezelfde lus, maar dan als coördinaat. Wat dit laat zien

Het kompas leest Hodge als een gesloten lus. Dat is geen bewijs dat de conjectuur waar is — het probleem staat nog open. Maar het laat zien dat de lezing past op de vergelijking.

En dat is het verschil met de vorige lezingen: bij Poincaré, Navier-Stokes en Yang-Mills was er een punt waar de vergelijking stopte of een punt dat niet bereikbaar was. Bij Riemann en BSD was er een as waar alles in evenwicht was. Hier is er een lus: een pad dat rondgaat en terugkomt. De vergelijking stopt niet, en er is geen as — er is een cyclus.

Dat is de derde lezing: niet een roll-over, niet een offset, niet een spiegelas, maar een gesloten lus. 3.7 P vs NP — dezelfde afstand De originele stelling

P vs NP gaat over computers. P is de klasse van problemen die snel opgelost kunnen worden. NP is de klasse van problemen waarvan een oplossing snel gecontroleerd kan worden.

De vraag is of P = NP: kan elk probleem dat snel gecontroleerd kan worden, ook snel opgelost worden?

Onbewezen sinds 1971. Een van de zeven millenniumprijsproblemen. Niemand heeft het opgelost. Niemand heeft het weerlegd. De originele formule text

P = NP?

De vraag is of de twee klassen gelijk zijn. Het kompas gebruiken

Het kompas leest P vs NP als een gesloten lus — dezelfde lezing als bij Hodge, maar met een andere invulling.

Vinden en controleren zijn dezelfde afstand. In base-10 worden P en NP voorgesteld als twee punten op een oneindige lijn: P is polynomiale tijd (n², n³), NP is exponentiële tijd (2ⁿ, 10ⁿ). De afstand tussen die punten lijkt astronomisch groot, en groeit met n. De liniaal suggereert dus sterk dat P ≠ NP.

Het kompas leest die afstand als een lus. Op een cirkel is de afstand tussen twee punten symmetrisch: van 12 naar 6 is even ver als van 6 naar 12. Je loopt over de omtrek, en de afstand is dezelfde, welke kant je ook op gaat.

De "astronomische kloof" is een vervorming. De kloof tussen P en NP is geen echte kloof. Het is de vervorming die optreedt als je een roterende bol platdrukt op een oneindige liniaal. Op de bol is de afstand symmetrisch.

De formule voor het kompas: text

P = afstand van A naar B (over de omtrek) NP = afstand van B naar A (over de omtrek)

Het kompas leest P en NP als dezelfde afstand: de afstand is symmetrisch. Wat dit laat zien

Het kompas leest P vs NP als een gesloten lus. Dat is geen bewijs dat P = NP — het probleem staat nog open. Maar het laat zien dat de lezing past op de vergelijking.

En dat is de overeenkomst met Hodge: beide vergelijkingen hebben een cyclus. Bij Hodge is dat de algebraïsche cyclus; bij P vs NP is dat de afstand die symmetrisch is. De lus is in beide gevallen hetzelfde: je begint bij het observatiepunt, je gaat rond, en je komt terug.

Dat is de derde lezing, voor de tweede keer: niet een roll-over, niet een offset, niet een spiegelas, maar een gesloten lus. 3.8 Fijnstructuur — de sprong naar de roll-over De originele stelling

De fijnstructuurconstante α bepaalt de sterkte van de elektromagnetische wisselwerking. De gemeten waarde is α ≈ 1/137,035999... De vraag is waarom deze waarde precies zo is. De originele formule text

α = e² / (4πε₀ħc) ≈ 1/137,035999...

Het kompas gebruiken

Het kompas leest de fijnstructuur als een offset — dezelfde lezing als bij Yang-Mills, maar met een andere invulling.

De constante begint niet bij nul. Er is een minimum: de 137. In base-10 is dat een harde muur. Maar het kompas leest de rest (0,035999...) als een sprong. De 137 is de eerste trede. De rest is de beweging naar de volgende laag.

De berekening:

0,035999177 × 60 = 2,15995... (2 stappen).

0,15995... × 60 = 9,597... (afgerond 9,6).

9,6 × 6 = 57,6. En 57,6 = 0,8 × 72°.

De formule voor het kompas: text

1/α = 137 + 2/60 + 9,6/3600 9,6 × 6 = 57,6 = 0,8 × 72

De 137 is de eerste trede. De 2 is de deler. En de 9,6 rolt via de operator om naar de rotatiesector. Wat dit laat zien

Het kompas leest de fijnstructuur als een offset. Dat is geen bewijs dat de fysica cyclisch is — de meting is wat hij is. Maar het laat zien dat de lezing past op de vergelijking.

En dat is de overeenkomst met Yang-Mills: beide vergelijkingen hebben een minimum dat niet nul is. Bij Yang-Mills is dat het massagat; bij de fijnstructuur is dat de 137. De sprong is in beide gevallen hetzelfde: je begint niet bij nul, maar bij een eerste trede. 3.9 Hiërarchie — de sprong naar de spiegelas De originele stelling

Waarom is de zwaartekracht 10³² keer zwakker dan de zwakke kernkracht? Dit is het hiërarchieprobleem. Onopgelost. De originele formule text

F_gravity / F_weak ≈ 10⁻³²

Het kompas gebruiken

Het kompas leest de hiërarchie als een offset — dezelfde lezing als bij Fijnstructuur en Yang-Mills.

De verhouding begint niet bij nul. Er is een minimum: de 10³². In base-10 is dat een onvoorstelbare kloof. Maar het kompas leest de kloof als een sprong.

De berekening:

Basis: 10 × 6 = 60. En 60 mod 60 = 0. (De lineaire basis klapt weg).

Exponent: 32 × 6 = 192. En 192 / 60 = 3 met een rest van 12.

De formule voor het kompas: text

10³² → (3, 12, 0) 12 = spiegelas (helft van 24)

De kloof rolt om naar de coördinaat (3, 12, 0). De restwaarde is 12, de spiegelas. Wat dit laat zien

Het kompas leest de hiërarchie als een offset. Dat is geen bewijs dat de fysica cyclisch is. Maar het laat zien dat de lezing past op de vergelijking.

En dat is de overeenkomst met Fijnstructuur: beide vergelijkingen hebben een minimum dat niet nul is. Bij Fijnstructuur is dat de 137; bij de hiërarchie is dat de 10³². De sprong is in beide gevallen hetzelfde: je begint niet bij nul, maar bij een eerste trede. 3.10 Zwart gat — de gesloten bol De originele stelling

Gaat informatie verloren wanneer een zwart gat verdampt? Dit is de informatieparadox van Hawking. Onopgelost sinds 1976. De originele formule text

S_BH = A / (4ℓ_P²)

De entropie van een zwart gat is evenredig met de oppervlakte van de horizon. Het kompas gebruiken

Het kompas leest het zwarte gat als een gesloten bol — dezelfde lezing als bij Hodge.

De horizon is een bol. De oppervlakte A is de oppervlakte van een bol. In het kompas is dat een gesloten oppervlak — een bol met straal r. De entropie is de oppervlakte van die bol.

De formule voor het kompas: text

S_BH = A / (4ℓ_P²) → A = 4πr² Een gesloten bol. Rotatie.

De horizon is de bol. De entropie is de oppervlakte. De informatie is de lus. Wat dit laat zien

Het kompas leest het zwarte gat als een gesloten bol. Dat is geen bewijs dat de informatieparadox is opgelost. Maar het laat zien dat de lezing past op de vergelijking.

En dat is de overeenkomst met Hodge: beide vergelijkingen hebben een gesloten lus. Bij Hodge is dat de algebraïsche cyclus; bij het zwarte gat is dat de horizon. De lus is in beide gevallen hetzelfde: je begint bij het observatiepunt, je gaat rond, en je komt terug. 3.11 Horizon — de uniforme bol De originele stelling

Waarom is de temperatuur van de kosmische achtergrondstraling aan alle kanten exact gelijk, terwijl die gebieden nooit contact hebben gehad? Dit is het horizonprobleem. Onopgelost sinds 1969. De originele formule text

T = 2,725 K (universeel)

Het kompas gebruiken

Het kompas leest de horizon als een gesloten bol — dezelfde lezing als bij Hodge en het zwarte gat.

De temperatuur is uniform. Overal hetzelfde. In het kompas is dat een bol waar alle punten dezelfde waarde hebben — een constante op de bol.

De formule voor het kompas: text

T = 2,725 K → uniforme bol Alle punten hebben dezelfde waarde.

De bol is de horizon. De temperatuur is de constante. De uniformiteit is de lus. Wat dit laat zien

Het kompas leest de horizon als een gesloten bol. Dat is geen bewijs dat het horizonprobleem is opgelost. Maar het laat zien dat de lezing past op de vergelijking.

En dat is de overeenkomst met het zwarte gat: beide vergelijkingen hebben een bol. Bij het zwarte gat is dat de horizon; bij de horizon is dat de temperatuur. De bol is in beide gevallen hetzelfde: een gesloten oppervlak waar alle punten meetellen. 3.12 Tijd — de roll-over van de hittedood De originele stelling

Waarom is er een richting in de tijd? De meeste fundamentele natuurwetten zijn tijdsymmetrisch, maar de werkelijkheid is dat niet. Onopgelost. De originele formule text

dS/dt ≥ 0

De tweede wet van de thermodynamica: de entropie neemt altijd toe. Het kompas gebruiken

Het kompas leest de tijd als een roll-over — dezelfde lezing als bij Poincaré en Navier-Stokes.

De pijl van de tijd is een richting. De tijd gaat vooruit, nooit achteruit. In het kompas is dat een richting in de bol — een pad dat van (0,0,0) naar (x,y,z) gaat en niet terug. Maar in de herziene lezing is dat een spiraal op een bol: je gaat vooruit én je rolt om. De hittedood is de roll-over.

De formule voor het kompas: text

dS/dt ≥ 0 → een spiraal op de bol De hittedood = de roll-over (60 = 0)

De tijd is de spiraal. De hittedood is de roll-over. De richting is de beweging. Wat dit laat zien

Het kompas leest de tijd als een roll-over. Dat is geen bewijs dat de tijd een richting heeft. Maar het laat zien dat de lezing past op de vergelijking.

En dat is de overeenkomst met Poincaré en Navier-Stokes: beide vergelijkingen hebben een punt waar de beweging stopt of omrolt. Bij Poincaré is dat de singulariteit; bij Navier-Stokes is dat de divergentie; bij de tijd is dat de hittedood. De roll-over is in alle gevallen hetzelfde: je rolt om, en de beweging gaat verder.

EINDE VAN HET DOCUMENT
