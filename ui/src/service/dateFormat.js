function epochToDate(value) {
	return new Date(value * 1000)
}

export function toDate(value) {
    return epochToDate(value).toLocaleDateString("ru-BY", {timeZone:"Europe/Minsk"})
}

export function toDateTime(value) {
	return epochToDate(value).toLocaleString("ru-BY", { timeZone: "Europe/Minsk" })
}
