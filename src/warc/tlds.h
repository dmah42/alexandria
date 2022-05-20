
#pragma once

#include <iostream>
#include <unordered_set>

namespace warc {

	const std::unordered_set<std::string> double_tlds({
		"co.uk"
	});

	const std::unordered_set<std::string> tlds({
		"se",
		"com",
		"org",
		"net",
		"int",
		"edu",
		"gov",
		"mil",
		"ad",
		"as",
		"az",
		"bz",
		"cc",
		"cd",
		"co",
		"dj",
		"fm",
		"gg",
		"io",
		"la",
		"me",
		"ms",
		"nu",
		"sc",
		"tf",
		"tv",
		"ws",
		"ai",
		"as",
		"au",
		"bm",
		"bs",
		"gi",
		"gu",
		"uk",
		"us",
		"sh",
		"ca",
		"to",
		"ac",
		"academy",
		"accountant",
		"accountants",
		"active",
		"actor",
		"ads",
		"adult",
		"aero",
		"africa",
		"agency",
		"airforce",
		"amazon",
		"analytics",
		"apartments",
		"app",
		"apple",
		"archi",
		"army",
		"art",
		"associates",
		"attorney",
		"auction",
		"audible",
		"audio",
		"author",
		"auto",
		"autos",
		"aws",
		"baby",
		"band",
		"bank",
		"bar",
		"barefoot",
		"bargains",
		"baseball",
		"basketball",
		"beauty",
		"beer",
		"best",
		"bestbuy",
		"bet",
		"bible",
		"bid",
		"bike",
		"bingo",
		"bio",
		"biz",
		"black",
		"blackfriday",
		"blockbuster",
		"blog",
		"blue",
		"boo",
		"book",
		"boots",
		"boston",
		"bot",
		"boutique",
		"box",
		"broadway",
		"broker",
		"build",
		"builders",
		"business",
		"buy",
		"buzz",
		"cab",
		"cafe",
		"call",
		"cam",
		"camera",
		"camp",
		"cancerresearch",
		"capital",
		"car",
		"cards",
		"care",
		"career",
		"careers",
		"cars",
		"case",
		"cash",
		"casino",
		"catering",
		"catholic",
		"center",
		"cern",
		"ceo",
		"cfd",
		"channel",
		"chat",
		"charity",
		"cheap",
		"christmas",
		"church",
		"circle",
		"city",
		"claims",
		"cleaning",
		"click",
		"clinic",
		"clothing",
		"cloud",
		"club",
		"coach",
		"codes",
		"coffee",
		"college",
		"community",
		"company",
		"compare",
		"computer",
		"condos",
		"construction",
		"consulting",
		"contact",
		"contractors",
		"cooking",
		"cool",
		"coop",
		"country",
		"coupon",
		"coupons",
		"courses",
		"cpa",
		"credit",
		"creditcard",
		"cruise",
		"cricket",
		"cruises",
		"cyou",
		"dad",
		"dance",
		"data",
		"date",
		"dating",
		"day",
		"deal",
		"deals",
		"degree",
		"delivery",
		"democrat",
		"dental",
		"dentist",
		"design",
		"dev",
		"diamonds",
		"diet",
		"digital",
		"direct",
		"directory",
		"discount",
		"diy",
		"docs",
		"doctor",
		"dog",
		"domains",
		"dot",
		"download",
		"drive",
		"duck",
		"earth",
		"eat",
		"eco",
		"education",
		"email",
		"energy",
		"engineer",
		"engineering",
		"edeka",
		"entertainment",
		"enterprises",
		"equipment",
		"esq",
		"estate",
		"events",
		"exchange",
		"expert",
		"exposed",
		"express",
		"fail",
		"faith",
		"family",
		"fan",
		"fans",
		"farm",
		"fashion",
		"fast",
		"feedback",
		"fiat",
		"film",
		"final",
		"finance",
		"financial",
		"fire",
		"fish",
		"fishing",
		"fit",
		"fitness",
		"flights",
		"florist",
		"flowers",
		"fly",
		"foo",
		"food",
		"foodnetwork",
		"football",
		"forsale",
		"forum",
		"foundation",
		"free",
		"frontdoor",
		"fun",
		"fund",
		"furniture",
		"fyi",
		"gallery",
		"game",
		"games",
		"garden",
		"gay",
		"gdn",
		"gift",
		"gifts",
		"gives",
		"glass",
		"gle",
		"global",
		"gold",
		"golf",
		"google",
		"gop",
		"graphics",
		"green",
		"gripe",
		"grocery",
		"group",
		"guide",
		"guitars",
		"guru",
		"hair",
		"hangout",
		"health",
		"healthcare",
		"help",
		"here",
		"hiphop",
		"hiv",
		"hockey",
		"holdings",
		"holiday",
		"homegoods",
		"homes",
		"homesense",
		"horse",
		"hospital",
		"host",
		"hosting",
		"hot",
		"hotels",
		"house",
		"how",
		"ice",
		"icu",
		"inc",
		"industries",
		"info",
		"ing",
		"ink",
		"institute[50]",
		"insurance",
		"insure",
		"international",
		"investments",
		"irish",
		"jewelry",
		"jobs",
		"joy",
		"kim",
		"kitchen",
		"kosher",
		"land",
		"lat",
		"law",
		"lawyer",
		"lease",
		"leclerc",
		"legal",
		"lgbt",
		"life",
		"lifeinsurance",
		"lighting",
		"like",
		"limited",
		"limo",
		"link",
		"live",
		"living",
		"loan",
		"loans",
		"locker",
		"lol",
		"lotto",
		"love",
		"ltd",
		"luxury",
		"makeup",
		"management",
		"map",
		"market",
		"marketing",
		"markets",
		"mba",
		"med",
		"media",
		"meet",
		"meme",
		"memorial",
		"men",
		"menu",
		"mint",
		"mobi",
		"mobile",
		"mobily",
		"moe",
		"mom",
		"money",
		"monster",
		"mortgage",
		"motorcycles",
		"mov",
		"movie",
		"museum",
		"music",
		"name",
		"navy",
		"network",
		"new",
		"news",
		"ngo",
		"ninja",
		"now",
		"ntt",
		"observer",
		"off",
		"org",
		"one",
		"ong",
		"onl",
		"online",
		"ooo",
		"open",
		"organic",
		"origins",
		"page",
		"partners",
		"parts",
		"party",
		"pay",
		"pet",
		"pharmacy",
		"phone",
		"photo",
		"photography",
		"photos",
		"physio",
		"pics",
		"pictures",
		"pid",
		"pin",
		"pink",
		"pizza",
		"place",
		"plumbing",
		"plus",
		"poker",
		"porn",
		"post",
		"press",
		"prime",
		"pro",
		"productions",
		"prof",
		"promo",
		"properties",
		"property",
		"protection",
		"pub",
		"qpon",
		"racing",
		"radio",
		"read",
		"realestate",
		"realtor",
		"realty",
		"recipes",
		"red",
		"rehab",
		"reit",
		"rent",
		"rentals",
		"repair",
		"report",
		"republican",
		"rest",
		"restaurant",
		"review",
		"reviews",
		"rich",
		"rip",
		"rocks",
		"rodeo",
		"room",
		"rugby",
		"run",
		"safe",
		"sale",
		"salon",
		"save",
		"sbi",
		"scholarships",
		"school",
		"science",
		"search",
		"secure",
		"security",
		"select",
		"services",
		"sex",
		"sexy",
		"shoes",
		"shop",
		"shopping",
		"show",
		"showtime",
		"silk",
		"singles",
		"site",
		"ski",
		"skin",
		"sky",
		"sling",
		"smile",
		"sncf",
		"soccer",
		"social",
		"software",
		"solar",
		"solutions",
		"song",
		"space",
		"spreadbetting",
		"spot",
		"sport",
		"storage",
		"store",
		"stream",
		"studio",
		"study",
		"style",
		"sucks",
		"supplies",
		"supply",
		"support",
		"surf",
		"surgery",
		"systems",
		"talk",
		"tattoo",
		"tax",
		"taxi",
		"team",
		"tech",
		"technology",
		"tel",
		"tennis",
		"theater",
		"theatre",
		"tickets",
		"tips",
		"tires",
		"today",
		"tools",
		"top",
		"tours",
		"town",
		"toys",
		"trade",
		"trading",
		"training",
		"travel",
		"travelersinsurance",
		"trust",
		"tube",
		"tunes",
		"uconnect",
		"university",
		"uno",
		"vacations",
		"ventures",
		"vet",
		"video",
		"villas",
		"vin",
		"vip",
		"vision",
		"vodka",
		"volvo",
		"vote",
		"voting",
		"voyage",
		"wang",
		"watch",
		"watches",
		"weather",
		"webcam",
		"website",
		"wed",
		"wedding",
		"whoswho",
		"wiki",
		"win",
		"wine",
		"winners",
		"work",
		"works",
		"world",
		"wow",
		"wtf",
		"xxx",
		"xyz",
		"yachts",
		"yoga",
		"you",
		"youtube",
		"zero",
		"zip",
		"zone"
	});
}
