function epochToDate(value) {
    return new Date(value * 1000)
}

export function toDate(value) {
    return epochToDate(value).toLocaleDateString()
}

export function toDateTime(value) {
    return epochToDate(value).toLocaleString()
}
